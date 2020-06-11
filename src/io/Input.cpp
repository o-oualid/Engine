#include "Input.h"
namespace Engine {
    bool Input::isKeyPressed(Input::Key key) {
        return glfwGetKey(window, (int) key) == GLFW_PRESS;
    }

    Input::Input() {

    }

    Input::Input(GLFWwindow *window) : window{window} {

    }

    Input::Point Input::getMousePos() {
        Point pos{};
        glfwGetCursorPos(window, &(pos.x), &(pos.y));
        if (pos.x != 0 || pos.y != 0) {
            return pos;
        }
        return pos;
    }

    void Input::HideCursor(bool flag) {
        if (flag)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    }

    bool Input::isMouseKeyPressed(Input::MouseKey key) {
        return glfwGetMouseButton(window, (int) key) == GLFW_PRESS;
    }
}