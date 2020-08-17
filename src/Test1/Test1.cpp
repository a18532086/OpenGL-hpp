
#include <gl.hpp>
#include <GLFW/glfw3.h>
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

        std::cout << OPENGL_HPP_DEFAULT_DISPATCHER.glGetString(GL_VERSION)
                  << std::endl;

        auto vaos = gl::createObjectv<gl::Buffer>(2);

        auto vao = gl::createObject<gl::VertexArray>();

        gl::deleteObject<gl::VertexArray>(gl::VertexArray{},
                                          OPENGL_HPP_DEFAULT_DISPATCHER);
        vao.destroy();

        vao.bind();

        auto buffers = gl::createObject<gl::Buffer,6>();

        gl::bindBuffersBase(gl::Buffer::BindBaseTarget::eUniformBuffer, 0, buffers);

        gl::deleteObject<gl::Buffer>(buffers);

        auto maxUBObinding =
            gl::get<int>(gl::StateVariables::eMaxUniformBufferBindings);

        std::vector<int> UBObinding(maxUBObinding);

        for (int i = 0; i < maxUBObinding; ++i) {
            UBObinding[i] =
                gl::get<int>(gl::StateVariables::eUniformBufferBinding, GLuint(i));
        }

        auto index = gl::get<GLint>(gl::StateVariables::eVertexArrayBinding);

        auto isDepTest = gl::get<bool>(gl::StateVariables::eDepthTest);

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
