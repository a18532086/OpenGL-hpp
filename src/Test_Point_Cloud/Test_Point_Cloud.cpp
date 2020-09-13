
#include <gl.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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

class App {
   private:
    GLFWwindow *window;
    gl::VertexArray vao;
    gl::Buffer vbo;
    gl::Buffer MVPUBObject;
    gl::Program program;
    std::size_t pointsCount;

    struct {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    } mvp;

    decltype(mvp) *mappedMVP;
    static constexpr auto &d = OPENGL_HPP_DEFAULT_DISPATCHER;
    void draw() {
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

        d.glDrawArrays(GL_POINTS, 0, pointsCount);
    }
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

   public:
    int w;
    int h;
    void initShader() {
        program = gl::createObject<gl::Program>();

        gl::Shader fs, vs;

        std::tie(fs, vs) = gl::arrayToTuple(gl::createObject<gl::Shader>(
            {gl::ShaderType::eFragmentShader, gl::ShaderType::eVertexShader}));

        vs.loadSource(VertexShader);
        fs.loadSource(FragShader);

        vs.compile();
        fs.compile();

        std::cout << "Vertex Shader Compile Info Log:\n"
                  << vs.getInfoLog() << std::endl;

        std::cout << "Fragment Shader Compile Info Log:\n"
                  << fs.getInfoLog() << std::endl;

        program.attachShaders({vs, fs});

        program.link();

        gl::deleteObject<gl::Shader>({vs, fs});

        std::cout << "Program Link Info Log:\n"
                  << program.getInfoLog() << std::endl;

        program.use();

        d.glEnable(GL_DEPTH_TEST);

        d.glDepthFunc(GL_LEQUAL);
    }
    void initWindow() {
        if (glfwInit() != GLFW_TRUE) {
            throw std::runtime_error("can not init GLFW !");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        if (!(window = glfwCreateWindow(800, 800, "test", nullptr, nullptr))) {
            throw std::runtime_error("can not create window !");
        }

        w = 800;
        h = 800;

        glfwMakeContextCurrent(window);

        glfwSetWindowUserPointer(window, this);

        glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int w, int h) {
            App *app =
                reinterpret_cast<App *>(glfwGetWindowUserPointer(window));
            app->w = w;
            app->h = h;
        });
    }
    void init() {
        initWindow();

        gl::initLoader(glfwGetProcAddress);

        std::boolalpha(std::cout);

        std::vector<glm::vec3> points{};
        {
            std::ifstream plyFile("bun_zipper.ply");
            std::string buf{};
            plyFile >> pointsCount;
            plyFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            points.resize(pointsCount);
            for (std::size_t i = 0; i < pointsCount; ++i) {
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
    void run() {
        init();
        mainLoop();
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
