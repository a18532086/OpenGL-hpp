#pragma once
#include <GLFW\glfw3.h>
#include <memory>
namespace WindowUtils {
class App {
   protected:
    GLFWwindow *window;
    App *thisApp;

   public:
    App(App *thisApp = nullptr,int w = 800,int h = 800):thisApp(thisApp),w(w),h(h),window(){};
    int w;
    int h;
    virtual void render() {

    }
    virtual void initWindow() {
        if (glfwInit() != GLFW_TRUE) {
            throw std::runtime_error("can not init GLFW !");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        if (!(window = glfwCreateWindow(w, h, "test", nullptr, nullptr))) {
            throw std::runtime_error("can not create window !");
        }

        glfwMakeContextCurrent(window);

        glfwSwapInterval(GLFW_TRUE);
    }
    virtual void init() {

    }
    virtual void run() {
        thisApp->initWindow();
        thisApp->init();
        while (!glfwWindowShouldClose(window)) {
            thisApp->render();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
};
}  // namespace MyNamespace