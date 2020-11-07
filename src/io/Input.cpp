#include "Input.h"

namespace Engine {
    bool Input::isKeyPressed(Input::Key key) {
        return glfwGetKey(window, (int) key) == GLFW_PRESS;
    }

    Input::Input() = default;

    Input::Input(GLFWwindow *window) : window{window} {
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);
        auto mouseCallBack = [](GLFWwindow *window, double x, double y) {
            auto *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
            input->mouseCallBack((float) x, (float) y);
        };
        glfwSetCursorPosCallback(window, mouseCallBack);
        auto keyCallBack = [](GLFWwindow *window, int button, int scancode, int action, int mods) {
            auto *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
            input->keyCallBack(Key(button), keyAction(action));
        };
        glfwSetKeyCallback(window, keyCallBack);
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
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    bool Input::isMouseKeyPressed(Input::MouseKey key) {
        return glfwGetMouseButton(window, (int) key) == GLFW_PRESS;
    }
    void Input::mouseCallBack(float x, float y) const {
        InputListener *currentMouseListener = inputListener;
        while (currentMouseListener != nullptr) {
            if (currentMouseListener->onMouseMoved(x, y)) return;
            currentMouseListener = currentMouseListener->nextListener;
        }
    }
    void Input::removeMouseListener(Input::InputListener *listener) {
        if (inputListener == listener) {
            inputListener = listener->nextListener;
            listener->nextListener = nullptr;
            return;
        }

        InputListener *current = inputListener;
        while (current != nullptr) {
            if (current->nextListener == listener) {
                current->nextListener = listener->nextListener;
                listener->nextListener = nullptr;
                return;
            }

            current = current->nextListener;
        }
    }
    void Input::addMouseListener(Input::InputListener *listener) {
        listener->nextListener = inputListener;
        inputListener = listener;
    }
    void Input::keyCallBack(Input::Key key, keyAction action) const {
        InputListener *currentMouseListener = inputListener;
        while (currentMouseListener != nullptr) {
            switch (action) {
                case keyAction::PRESS:
                    if (currentMouseListener->onKeyPressed(key)) return;
                    break;
                case keyAction::RELEASE:
                    if (currentMouseListener->onKeyReleased(key)) return;
                    break;
            }

            currentMouseListener = currentMouseListener->nextListener;
        }
    }

}// namespace Engine