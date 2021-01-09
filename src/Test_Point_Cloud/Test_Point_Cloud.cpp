
#include <gl.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Utils\WindowUtils.h>

#include <chrono>
#include <fstream>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string VertexShader = R"(
    #version 450
    layout (location = 1) in vec3 pointPos;
    layout (binding = 2,std140) uniform MVP{
        mat4 model;
        mat4 view;
        mat4 proj;
    };
    out VS_OUT{
        vec3 color; 
    }vs_out;
    void main(){
        mat4 mvp = proj * view * model;
        gl_Position = mvp * vec4(pointPos,1.0);
        vs_out.color = vec3(sin(gl_Position) * sin(gl_Position));
    }
)";

std::string FragShader = R"(
    #version 450
    out vec4 color;
    in VS_OUT{
        vec3 color; 
    }vs_in;
    void main(){
        color = vec4(vs_in.color,1.0);
    }
)";

class App : public WindowUtils::App {
   private:
    gl::VertexArray vao;
    gl::Buffer vbo;
    gl::Buffer MVPUBObject;
    gl::Program fwdProgram;
    std::size_t primitivesCount;

    struct ST_MVP {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    } mvp;

    ST_MVP *mappedMVP;
    static constexpr auto &d = OPENGL_HPP_DEFAULT_DISPATCHER;
    void render() {
        d.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        d.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        d.glPointSize(1.0f);
        d.glViewport(0, 0, w, h);

        float aspect = 1.0f * w / h;

        mvp.proj = glm::perspective(glm::radians(80.0f), aspect, 0.1f, 1000.0f);

        mvp.model =
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 5.0f)) *
            glm::scale(glm::mat4{1.0f}, glm::vec3{30.0f}) *
            glm::rotate(
                glm::mat4{1.0f},
                glm::radians(
                    0.1f *
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now().time_since_epoch())
                        .count()),
                glm::vec3(0.0f, 1.0f, 0.0f));

        mvp.view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));

        *mappedMVP = mvp;

        MVPUBObject.flushMappedRange(0, sizeof(mvp));

        d.glDrawArrays(GL_POINTS, 0, primitivesCount);
    }

   public:
    App()
        : WindowUtils::App(this),
          primitivesCount(),
          mvp(),
          vao(),
          vbo(),
          MVPUBObject(),
          mappedMVP(),
          fwdProgram()
    {}
    void initShader() {
        fwdProgram = gl::createObject<gl::Program>();

        gl::Shader fs, vs;

        std::tie(fs, vs) = gl::createObject<gl::Shader>(
            {gl::ShaderType::eFragmentShader, gl::ShaderType::eVertexShader});

        bool isDepTest =
            gl::get<bool>(gl::StateVariables::eDepthTest);

        vs.loadSource(VertexShader);
        fs.loadSource(FragShader);

        vs.compile();
        fs.compile();

        std::cout << "Vertex Shader Compile Info Log:\n"
                  << vs.getInfoLog() << std::endl;

        std::cout << "Fragment Shader Compile Info Log:\n"
                  << fs.getInfoLog() << std::endl;

        fwdProgram.attachShaders({vs, fs});

        fwdProgram.link();

        gl::deleteObject<gl::Shader>({vs, fs});

        std::cout << "Program Link Info Log:\n"
                  << fwdProgram.getInfoLog() << std::endl;

        fwdProgram.use();

        d.glEnable(GL_DEPTH_TEST);

        isDepTest = gl::get<bool>(gl::StateVariables::eDepthTest);

        d.glDepthFunc(GL_LEQUAL);
    }
    void init() {
        glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int w, int h) {
            App *app =
                reinterpret_cast<App *>(glfwGetWindowUserPointer(window));
            app->w = w;
            app->h = h;
        });

        glfwSetWindowUserPointer(window, this);

        gl::initLoader(glfwGetProcAddress);

        std::boolalpha(std::cout);

        std::vector<glm::vec3> points{};
        {
            std::ifstream plyFile("bun_zipper.ply");
            std::string buf{};
            constexpr auto &kPrefix = "element vertex";
            do {
                std::getline(plyFile, buf);
                if (buf.find(kPrefix) != std::string::npos) {
                    primitivesCount = std::atoi(buf.data() + std::size(kPrefix));
                }

            } while (buf.find("end_header") == std::string::npos);
            points.resize(primitivesCount);
            for (std::size_t i = 0; i < primitivesCount; ++i) {
                std::getline(plyFile, buf);
                std::istringstream(buf) >> points[i].x >> points[i].y >>
                    points[i].z;
            }
        }

        vao = gl::createObject<gl::VertexArray>();

        vbo = gl::createObject<gl::Buffer>();

        GLsizeiptr pointsSize = sizeof(points[0]) * points.size();

        vbo.createStorage(pointsSize, points.data(),
                          gl::BufferStorageFlagBits::eMapReadBit);

        vao.attribBinding(1, 0);

        vao.attributeFormat(1, 3, gl::VertexArray::AttributeType::eFloat, false,
                            0);

        vao.bindVertexBuffers(0, vbo, {0}, sizeof(points[0]));

        vao.enableAttribute(1);

        initShader();

        vao.bind();

        MVPUBObject = gl::createObject<gl::Buffer>();

        MVPUBObject.createStorage(
            sizeof(mvp), nullptr,
            gl::BufferStorageFlagBits::eMapWriteBit |
                gl::BufferStorageFlagBits::eMapPersistentBit);

        MVPUBObject.bindBase(gl::BufferBindBaseTarget::eUniformBuffer, 2);

        mappedMVP = MVPUBObject.mapRange<decltype(mvp) *>(
            0, sizeof(mvp),
            gl::BufferAccessFlagBits::eMapPersistentBit |
                gl::BufferAccessFlagBits::eMapWriteBit |
                gl::BufferAccessFlagBits::eMapFlushExplicitBit);

        gl::Error e{};

        while ((e = gl::getError()) != gl::Error::eNoError) {
            std::cout << gl::to_string(e) << std::endl;
        }
    }
};
int main() {
    try {
        App app{};
        app.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
