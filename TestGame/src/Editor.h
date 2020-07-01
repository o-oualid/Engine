#pragma once

#include <ui/Widget.h>
#include <string>
#include "entt/entity/registry.hpp"

class Editor : public Engine::Widget {
    entt::registry &registry;
public:
    Editor(entt::registry &registry);

    void draw() override;

private:
    void directoryContent(std::string path);

    static std::string getFileName(const std::string &path);
};
