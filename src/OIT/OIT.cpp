
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
    layout (binding = 2, std140) uniform MVP{
        mat4 model;
        mat4 view;
        mat4 proj;
    };
    out VS_OUT{
        vec4 color; 
    }vs_out;
    void main(){
        gl_Position = model * vec4(pointPos,1.0);
        vs_out.color = vec4(sin(gl_Position) * sin(gl_Position));
        vs_out.color.a = 0.8;
        gl_Position = proj * view * gl_Position;
    }
)";

std::string FragShader = R"(
    #version 450
    layout (early_fragment_tests) in;
    layout (binding = 0, std430) buffer SSHead {
        int head_pointer[];
    };
    struct My_Node{
        int last_ptr;
        uint packedColor1;
        uint packedColor2;
        uint packedDepth;
        
    };
    layout (binding = 1, std430) buffer writeonly SSLK {
        My_Node list_buffer[];
    };
    layout (binding = 0, offset = 0) uniform atomic_uint idx_cnt;
    layout (binding = 1, std140) uniform UB_ScreenSize {
        ivec2 screenSize;
    };
    
    in VS_OUT{
        vec4 color; 
    }vs_in;
    void main(){
        vec4 color = vec4(vs_in.color);
        uint now_idx = atomicCounterIncrement(idx_cnt);
        int last_ptr = atomicExchange(head_pointer[int(gl_FragCoord.x + gl_FragCoord.y * screenSize.x)],int(now_idx));
        My_Node item;
        item.last_ptr = last_ptr;
        item.packedColor1 = packUnorm2x16(color.xy);
        item.packedColor2 = packUnorm2x16(color.zw);
        item.packedDepth = floatBitsToUint(gl_FragCoord.z);
        list_buffer[now_idx] = item;
    }
)";

std::string VertexShader2 = R"(
    #version 450
    void main(){
        vec2[] points = vec2[](
                        vec2(-1.0,1.0),
                        vec2(-1.0,-1.0),
                        vec2(1.0,1.0),
                        vec2(1.0,-1.0)
                        );
        gl_Position = vec4(points[gl_VertexID],0.0,1.0);
    }
)";

std::string FragShader2 = R"(
    #version 450
    layout (binding = 0, std430) buffer readonly SSHead {
        int head_pointer[];
    };
    struct My_Node{
        int last_ptr;
        uint packedColor1;
        uint packedColor2;
        uint packedDepth;
    };
    layout (binding = 1, std430) buffer readonly SSLK {
        My_Node list_buffer[];
    };
    layout (binding = 2, std430) buffer SSHeap {
        uint map_heap_cnt;
        uint map_heap[];
    };
    layout (binding = 1, std140) uniform UB_ScreenSize {
        ivec2 screenSize;
    };

    out vec4 color;
    #define left(x) ((x) << 1) + 1
    #define right(x) ((x) << 1) + 2
    #define depth_unpack(x) uintBitsToFloat(list_buffer[map_heap[x]].packedDepth)
    #define color_unpack(x) vec4(unpackUnorm2x16(list_buffer[map_heap[x]].packedColor1), unpackUnorm2x16(list_buffer[map_heap[x]].packedColor2))
    
    bool cmp_function(uint lhs, uint rhs){
        return depth_unpack(lhs) > depth_unpack(rhs);
    }
    
    
    void swap(inout uint lhs,inout uint rhs){
        uint tmp = rhs;
        rhs = lhs;
        lhs = tmp;
    }
    void max_heapify(uint i, uint n, uint st){
        uint largest = i;
        do{
            swap(map_heap[i],map_heap[largest]);
            i = largest;
            uint l = left(i - st) + st;
            uint r = right(i - st) + st;
            if(l < n && cmp_function(largest, l)){
                largest = l;
            }
            if(r < n && cmp_function(largest, r)){
                largest = r;
            }
        } while(largest != i);
    }
    void build_max_heap(uint st,uint ed){
        uint n = ed - st;
        for (uint i = n / 2; i > 0; --i){
            max_heapify(st + i - 1, ed, st);
        }
    }
    void heap_sort(uint st, uint ed){
        build_max_heap(st, ed);
        for (uint i = ed; i > st + 1; --i){
            swap(map_heap[st],map_heap[i - 1]);
            max_heapify(st, i - 1, st);
        }
    }
    void build_max_heap_array(out uint st, out uint ed){
        int pHead = head_pointer[int(gl_FragCoord.x + gl_FragCoord.y * screenSize.x)];
        int pIdx = pHead;
        uint cnt = 0;
        while(pIdx != -1){
            ++cnt;
            pIdx = list_buffer[pIdx].last_ptr;
        }
        st = atomicAdd(map_heap_cnt, cnt);
        ed = st + cnt;
        pIdx = pHead;
        cnt = st;
        while(pIdx != -1){
            map_heap[cnt++] = pIdx;
            pIdx = list_buffer[pIdx].last_ptr;
        }
    }
    vec4 blend(vec4 src, vec4 dst){
        return mix(dst, src , src.a);
    }
    void bubble_sort(uint st,uint ed){
        for (uint i = st;i < ed;++i){
            for (uint j = i + 1;j < ed;++j){
                if (!cmp_function(i, j)){
                    swap(map_heap[i],map_heap[j]);
                }
            }
        }
    }
    void main(){
        uint st = 0;
        uint ed = 0;
        build_max_heap_array(st, ed);
        heap_sort(st, ed);
        //bubble_sort(st, ed);
        color = vec4(0.0, 0.0, 0.0, 1.0);
        for (; st != ed; ++st){
            color = blend(color_unpack(st), color);
        }
    }
)";

class App : public WindowUtils::App {
   private:
    gl::VertexArray vao;
    gl::Buffer vbo;
    gl::Buffer ebo;
    gl::Buffer MVPUBObject;
    gl::Buffer sourceInitBuffer;
    gl::Buffer linkListBuffer;
    gl::Buffer headBuffer;
    gl::Buffer heapBuffer;
    gl::Buffer atomicBuffer;
    gl::Buffer whUniformBuffer;
    gl::Program fwdProgram;
    gl::Program lastProgram;
    std::size_t primitivesCount;

    struct ST_MVP {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    } mvp;

    ST_MVP *mappedMVP;
    GLuint *pMapAtomicCounter;
    GLuint *pMapHeapCnt;
    static constexpr auto &d = OPENGL_HPP_DEFAULT_DISPATCHER;
    void render() {

        vao.bind();

        d.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        d.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        d.glViewport(0, 0, w, h);

        float aspect = 1.0f * w / h;

        mvp.proj = glm::perspective(glm::radians(80.0f), aspect, 0.1f, 1000.0f);

        mvp.model =
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) *
            glm::scale(glm::mat4{1.0f}, glm::vec3{2.3f});

        glm::vec3 lookAtPos =
            glm::rotate(
                glm::mat4{1.0f},
                glm::radians(
                    0.01f *
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now().time_since_epoch())
                        .count()),
                glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::vec4(0.0f, 0.0f, -6.0f, 1.0f);

        mvp.view = glm::lookAt(lookAtPos, glm::vec3(0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));

        *mappedMVP = mvp;

        MVPUBObject.flushMappedRange(0, sizeof(ST_MVP));

        *pMapAtomicCounter = 0;

        atomicBuffer.flushMappedRange(0, sizeof(GLuint));

        d.glCopyNamedBufferSubData(
            static_cast<GLuint>(sourceInitBuffer),
            static_cast<GLuint>(headBuffer), 0, 0,
            static_cast<std::size_t>(w) * h * sizeof(GLuint));

        fwdProgram.use();

        d.glDrawElements(GL_TRIANGLES, primitivesCount, GL_UNSIGNED_INT,
                         nullptr);

        *pMapHeapCnt = 0;

        heapBuffer.flushMappedRange(0, sizeof(GLuint));

        lastProgram.use();

        //vao.unBind();

        d.glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    }

   public:
    App()
        : WindowUtils::App(this),
          primitivesCount(),
          pMapAtomicCounter(),
          pMapHeapCnt(),
          MVPUBObject(),
          mappedMVP() {}
    void initBuffer() {
        const glm::ivec2 wh(w, h);
        std::size_t pixelCnts = static_cast<std::size_t>(w) * h;
        std::tie(headBuffer, linkListBuffer, sourceInitBuffer, whUniformBuffer,
                 heapBuffer) = gl::createObject<gl::Buffer, 5>();

        sourceInitBuffer.initData(pixelCnts * sizeof(GLuint), nullptr,
                                  gl::BufferUsage::eStaticDraw);
        headBuffer.initData(pixelCnts * sizeof(GLuint), nullptr,
                            gl::BufferUsage::eDynamicCopy);
        linkListBuffer.initData(pixelCnts * sizeof(glm::vec4) * 3, nullptr,
                                gl::BufferUsage::eDynamicCopy);
        heapBuffer.initData((pixelCnts * 3 + 1) * sizeof(GLuint), nullptr,
                            gl::BufferUsage::eDynamicCopy);
        whUniformBuffer.initData(sizeof(glm::ivec2), &wh,
                                 gl::BufferUsage::eDynamicCopy);

        headBuffer.bindBase(gl::BufferBindBaseTarget::eShaderStorageBuffer, 0);

        heapBuffer.bindBase(gl::BufferBindBaseTarget::eShaderStorageBuffer, 2);

        linkListBuffer.bindBase(gl::BufferBindBaseTarget::eShaderStorageBuffer,
                                1);

        whUniformBuffer.bindBase(gl::BufferBindBaseTarget::eUniformBuffer, 1);

        {
            auto pBuffer =
                sourceInitBuffer.map<GLuint *>(gl::BufferAccess::eWriteOnly);
            std::memset(pBuffer, 0xff, pixelCnts * sizeof(GLuint));
            sourceInitBuffer.unmap();
        }

        pMapHeapCnt = heapBuffer.mapRange<GLuint *>(
            0, sizeof(GLuint),
            gl::BufferAccessFlagBits::eMapPersistentBit |
                gl::BufferAccessFlagBits::eMapWriteBit |
                gl::BufferAccessFlagBits::eMapFlushExplicitBit);
    }
    void destroyBuffer() {
        gl::deleteObject<gl::Buffer>({headBuffer, linkListBuffer,
                                      sourceInitBuffer, whUniformBuffer,
                                      heapBuffer});
    }
    void initShader() {
        std::tie(fwdProgram, lastProgram) = gl::createObject<gl::Program, 2>();

        gl::Shader fs, vs;

        std::tie(fs, vs) = gl::createObject<gl::Shader>(
            {gl::ShaderType::eFragmentShader, gl::ShaderType::eVertexShader});

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

        std::cout << "Program Link Info Log:\n"
                  << fwdProgram.getInfoLog() << std::endl;

        vs.loadSource(VertexShader2);
        fs.loadSource(FragShader2);

        vs.compile();
        fs.compile();

        std::cout << "Vertex Shader Compile Info Log:\n"
                  << vs.getInfoLog() << std::endl;

        std::cout << "Fragment Shader Compile Info Log:\n"
                  << fs.getInfoLog() << std::endl;

        lastProgram.attachShaders({vs, fs});

        lastProgram.link();

        std::cout << "Program Link Info Log:\n"
                  << lastProgram.getInfoLog() << std::endl;

        gl::deleteObject<gl::Shader>({vs, fs});

        // d.glEnable(GL_DEPTH_TEST);

        // d.glEnable(GL_BLEND);

        // d.glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // d.glDepthFunc(GL_LEQUAL);
    }
    void init() {
        glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int w, int h) {
            App *app =
                reinterpret_cast<App *>(glfwGetWindowUserPointer(window));
            app->w = w;
            app->h = h;
            app->destroyBuffer();
            app->initBuffer();
        });

        glfwSetWindowUserPointer(window, this);

        gl::initLoader(glfwGetProcAddress);

        std::boolalpha(std::cout);

        std::vector<glm::vec3> vertices{};
        std::vector<glm::uvec3> vertexIndices{};

        {
            std::ifstream objFile("suzanne.obj");
            std::string buf{};
            std::uint32_t st{};

            while (std::getline(objFile, buf)) {
                if (buf.find("v ") == 0) {
                    glm::vec3 v{};
                    if (3 != std::sscanf(buf.data() + 2, "%f%f%f", &v.x, &v.y,
                                         &v.z)) {
                        throw std::runtime_error("invalid format !");
                    }
                    vertices.push_back(v);
                } else if (buf.find("f ") == 0) {
                    glm::uvec3 v{};
                    if (3 != std::sscanf(buf.data() + 2,
                                         "%u/%*u/%*u%u/%*u/%*u%u/%*u/%*u", &v.x,
                                         &v.y, &v.z)) {
                        throw std::runtime_error("invalid format !");
                    }
                    v -= glm::uvec3(st, st, st);
                    vertexIndices.push_back(v);
                } else if (buf.find("s ") == 0) {
                    if (1 != std::sscanf(buf.data() + 2, "%u", &st)) {
                        throw std::runtime_error("invalid format !");
                    }
                }
            }
        }

        vao = gl::createObject<gl::VertexArray>();

        std::tie(vbo, ebo, atomicBuffer, MVPUBObject) =
            gl::createObject<gl::Buffer, 4>();

        GLsizeiptr pointsSize = sizeof(vertices[0]) * vertices.size();
        GLsizeiptr indicesSize =
            sizeof(vertexIndices[0]) * vertexIndices.size();

        primitivesCount = indicesSize;

        // init Buffers
        vbo.createStorage(pointsSize, vertices.data(),
                          gl::BufferStorageFlagBits::eMapReadBit);

        ebo.createStorage(indicesSize, vertexIndices.data(),
                          gl::BufferStorageFlagBits::eMapReadBit);

        atomicBuffer.createStorage(
            sizeof(GLuint), nullptr,
            gl::BufferStorageFlagBits::eMapPersistentBit |
                gl::BufferStorageFlagBits::eMapWriteBit);

        atomicBuffer.bindBase(gl::BufferBindBaseTarget::eAtomicCounterBuffer,
                              0);

        MVPUBObject.createStorage(
            sizeof(mvp), nullptr,
            gl::BufferStorageFlagBits::eMapWriteBit |
                gl::BufferStorageFlagBits::eMapPersistentBit);

        MVPUBObject.bindBase(gl::BufferBindBaseTarget::eUniformBuffer, 2);

        // config VAO

        vao.attribBinding(1, 0);

        vao.attributeFormat(1, 3, gl::VertexArray::AttributeType::eFloat, false,
                            0);

        vao.bindVertexBuffer(0, vbo, 0, sizeof(vertices[0]));

        vao.enableAttribute(1);

        vao.bindElementBuffer(ebo);

        initShader();

        vao.bind();

        // map
        mappedMVP = MVPUBObject.mapRange<ST_MVP *>(
            0, sizeof(ST_MVP),
            gl::BufferAccessFlagBits::eMapPersistentBit |
                gl::BufferAccessFlagBits::eMapWriteBit |
                gl::BufferAccessFlagBits::eMapFlushExplicitBit);

        pMapAtomicCounter = atomicBuffer.mapRange<GLuint *>(
            0, sizeof(GLuint),
            gl::BufferAccessFlagBits::eMapPersistentBit |
                gl::BufferAccessFlagBits::eMapWriteBit |
                gl::BufferAccessFlagBits::eMapFlushExplicitBit);

        initBuffer();

        gl::Error e{};

        while ((e = gl::getError()) != gl::Error::eNoError) {
            std::cout << gl::to_string(e) << std::endl;
        }
    }

    void destroy() {
        MVPUBObject.unmap();
        atomicBuffer.unmap();
        destroyBuffer();
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
