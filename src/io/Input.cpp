#include "Input.h"

bool Input::isKeyPressed(Input::Key key) {
    return glfwGetKey(window, (int) key) == GLFW_PRESS;
}

Input::Input() {

}

Input::Input(GLFWwindow *window) : window{window} {

}
