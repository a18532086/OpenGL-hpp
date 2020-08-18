
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <gl.hpp>
#include <functional>

#include <iostream>
#include <stdexcept>

OPENGL_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

class App {
   private:
    GLFWwindow *window;
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

   public:
    void init() { 
        if (glfwInit() != GLFW_TRUE) {
            throw std::runtime_error("can not init GLFW !");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        if (!(window = glfwCreateWindow(800, 800, "test", nullptr, nullptr))) {
            throw std::runtime_error("can not create window !");
        }

        glfwMakeContextCurrent(window);

        gl::initLoader(glfwGetProcAddress);

        GLuint maxExtension = gl::get<int>(gl::StateVariables::eNumExtensions);

        for (std::size_t i = 0; i < maxExtension; ++i) {
            std::cout << gl::getString(gl::ConnectionState::eExtensions, i)
                      << std::endl;
        }

        auto blend_color = gl::get<GLfloat,4>(gl::StateVariables::eColorClearValue);

        auto MaxtSize = gl::get<int64_t>(gl::StateVariables::eMax3dTextureSize);

        auto vao = gl::createObject<gl::VertexArray>();

        auto ebo = gl::createObject<gl::Buffer>();

        ebo.bind(gl::Buffer::BindTarget::eElementArrayBuffer);

        vao.bindElementBuffer(ebo);

        gl::Error e;

        while ((e = gl::getError()) != gl::Error::eNoError)
        {
            std::cout << gl::to_string(e) << std::endl;
        }

        gl::deleteObject<gl::VertexArray>(vao);

        using k = gl::_member_pointer_extract_class_t<decltype(gl::Buffer::template createFunc<gl::DispatchLoaderDynamic>)>;
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
