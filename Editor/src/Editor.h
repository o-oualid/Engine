#pragma once

#include "entt/entity/registry.hpp"
#include "logger/EditorLogger.h"
#include <renderer/vulkan/VkRenderer.h>
#include <string>
#include <ui/Widget.h>

class Editor : public Engine::Widget {
    entt::registry &registry;
    entt::entity selectedEntity = entt::null;
    Engine::VkRenderer *renderer;
    VkSampler sampler;
    Engine::VkTexture texture;
    std::string selectedFile{};
    std::string currentFile{};
    EditorLogger logger = EditorLogger{};

public:
    Editor(entt::registry &registry, Engine::VkRenderer *renderer);

    void init();

    void draw() override;

    ~Editor();

private:
    void drawDockSpace();

    void drawHierarchy();

    void drawEntityNode(entt::entity entity);

    void drawProperties();

    void drawAssets();

    void drawScene();

    void directoryContent(std::string path);

    static std::string getFileName(const std::string &path);

    void initSampler();

    void setStyle();

    bool hasEnding(const std::string &fullString, const std::string &ending);

    entt::entity getSelectedEntity();
};
