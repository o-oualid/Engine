#include "Editor.h"
#include "components/Car.h"
#include <components/Name.h>
#include <components/Relationship.h>
#include <filesystem>
#include <glm/gtx/intersect.hpp>
#include <imgui_impl_vulkan.h>


using namespace Engine;

Editor::Editor(entt::registry &registry, Engine::VkRenderer *renderer) : registry{registry}, renderer{renderer} {
}

void Editor::init() {
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //initSampler();
    setStyle();
    Engine::Log::logger = &logger;
}

void Editor::draw() {
    //ImGui::ShowDemoWindow();
    //selectedEntity = getSelectedEntity();

    drawDockSpace();
    drawHierarchy();
    drawProperties();
    drawAssets();
    drawScene();
    logger.draw();
    // ImGui::ShowStyleEditor(0);
}


void Editor::directoryContent(std::string path) {
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        ImGuiTreeNodeFlags flags =
                ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
        if (entry.is_directory()) {
            if (ImGui::TreeNode(getFileName(entry.path().string()).c_str())) {
                directoryContent(entry.path().string());
                ImGui::TreePop();
            }
        } else {
            if (selectedFile == entry.path().string()) flags |= ImGuiTreeNodeFlags_Selected;
            ImGui::TreeNodeEx("Object", flags, "%s", getFileName(entry.path().string()).c_str());
            if (ImGui::IsItemClicked()) {
                selectedFile = entry.path().string();
                if (hasEnding(selectedFile, ".gltf") || hasEnding(selectedFile, ".glb"))
                    selectedEntity = renderer->addModel(entry.path().string());
            }
        }
    }
}

std::string Editor::getFileName(const std::string &path) {
    return path.substr(path.find_last_of('\\') + 1);
}


void Editor::drawDockSpace() {

    static ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetWorkPos());
    ImGui::SetNextWindowSize(viewport->GetWorkSize());
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                    ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    bool open = true;
    ImGui::Begin("DockSpace", &open, window_flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    ImGuiIO &io = ImGui::GetIO();
    ImGuiID dockSpaceId = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), dockSpaceFlags);

    ImGui::End();
}

void Editor::drawHierarchy() {
    ImGui::Begin("Hierarchy");
    if (ImGui::Button("Add Entity"))
        selectedEntity = registry.create();

    entt::registry &reg = registry;
    auto &sel = selectedEntity;
    registry.each([&reg, &sel](auto entity) {
        std::string name = "null";
        if (reg.has<Name>(entity))
            name = reg.get<Name>(entity).name;

        static bool closable_group = true;
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth |
                                   ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen |
                                   ImGuiTreeNodeFlags_Bullet;
        if (entity == sel) flags |= ImGuiTreeNodeFlags_Selected;
        ImGui::TreeNodeEx((std::to_string((uint32_t) entity)).c_str(), flags, "%s",
                          (name + ": " + std::to_string((uint32_t) entity)).c_str());
        if (ImGui::IsItemClicked())
            sel = entity;

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("remove")) reg.destroy(entity);
            if (ImGui::MenuItem("duplicate"))
                ;

            ImGui::EndPopup();
        }
    });
    ImGui::End();
}

void Editor::drawProperties() {
    ImGui::Begin("Properties");
    if (registry.valid(selectedEntity) && selectedEntity != entt::null) {
        if (registry.has<Name>(selectedEntity)) {
            std::string &name = registry.get<Name>(selectedEntity).name;
            ImGui::InputText("Name", name.data(), name.capacity() - 1);

        } else if (ImGui::Button("add Name")) {
            registry.emplace<Name>(selectedEntity, "new Name");
        }

        if (registry.has<Transform>(selectedEntity)) {
            auto &t = registry.get<Transform>(selectedEntity);
            if (ImGui::TreeNode("Transform")) {
                ImGui::InputFloat3("Location##", &t.location.x);
                ImGui::InputFloat3("Scale", &t.scale.x);
                ImGui::InputFloat4("Rotation", &t.rotation.x);
                if (ImGui::IsItemEdited()) t.rotation = glm::normalize(t.rotation);
                t.dirty = true;
                ImGui::TreePop();
                ImGui::Separator();
            }
        } else if (ImGui::Button("add Transform")) {
            registry.emplace<Transform>(selectedEntity);
        }
        if (registry.has<Mesh>(selectedEntity)) {

            auto &mesh = registry.get<Mesh>(selectedEntity);
            if (ImGui::TreeNode("Colors")) {
                for (int i = 0; i < mesh.attributes.size(); i++)
                    ImGui::ColorEdit4(("Color " + std::to_string(i)).c_str(),
                                      &mesh.attributes[i].material.color.x);
                ImGui::TreePop();
                ImGui::Separator();
            }
        }
        if (registry.has<Relationship>(selectedEntity)) {
            auto &relation = registry.get<Relationship>(selectedEntity);
            if (ImGui::TreeNode("Parent")) {
                if (registry.valid(relation.parent)) {
                    ImGui::InputScalar("Id", ImGuiDataType_U32, &relation.parent);
                    if (registry.has<Name>(relation.parent))
                        ImGui::Text("%s", registry.get<Name>(relation.parent).name.c_str());
                } else {
                    //ImGui::PushStyleColor();
                    ImGui::InputScalar("Parent", ImGuiDataType_U32, &relation.parent);
                    // ImGui::PopStyleColor();
                }
                ImGui::TreePop();
                ImGui::Separator();
            }
        } else if (ImGui::Button("add Parent"))
            registry.emplace<Relationship>(selectedEntity, selectedEntity);

        if (registry.has<Car>(selectedEntity)) {
            auto &car = registry.get<Car>(selectedEntity);
            ImGui::InputFloat("Speed", &car.speed);
        } else if (ImGui::Button("add Car")) {
            registry.emplace<Car>(selectedEntity, 0.0f);
        }
    }
    ImGui::End();
}

void Editor::drawAssets() {
    ImGui::Begin("Assets");
    directoryContent(".\\data");
    ImGui::End();
}

void Editor::drawScene() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar;
    bool open = true;
    ImGui::Begin("Scene", &open, window_flags);
    ImGui::PopStyleVar();
    if (!selectedFile.empty()) {
        if (currentFile != selectedFile) {
            if (hasEnding(selectedFile, ".png")) {
                if (!currentFile.empty()) texture.free(renderer->device);
                texture = renderer->createTexture(selectedFile);
                currentFile = selectedFile;
            }
        }
        if (currentFile == selectedFile) {
            float width, height;
            if (ImGui::GetWindowSize().x * texture.height / texture.width <= ImGui::GetWindowSize().y) {
                width = ImGui::GetWindowSize().x;
                height = ImGui::GetWindowSize().x * texture.height / texture.width;
            } else {
                width = ImGui::GetWindowSize().y * texture.width / texture.height;
                height = ImGui::GetWindowSize().y;
            }
            ImGui::Image(ImGui_ImplVulkan_AddTexture(texture.sampler, texture.view,
                                                     VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL),
                         {width, height});
        }
    }

    ImGui::End();
}

bool Editor::hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

entt::entity Editor::getSelectedEntity() {
    entt::entity clickedEntity = entt::null;
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left, false)) {
        glm::vec2 mousePos = {ImGui::GetMousePos().x, ImGui::GetMousePos().y};

        auto cameraTransform = renderer->getGlobalTransform(renderer->camera);
        auto cameraView = glm::inverse(cameraTransform);
        auto cameraProjection = registry.get<PerspectiveCamera>(renderer->camera).projection();
        int width, height;
        renderer->window->getFramebufferSize(width, height);
        float x = (2.0f * mousePos.x) / width - 1.0f;
        float y = 1.0f - (2.0f * mousePos.y) / height;
        glm::vec4 ray_clip = glm::vec4(x, y, -1.0f, 1.0f);
        glm::vec4 ray_eye = glm::inverse(cameraProjection) * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
        glm::vec3 ray_wor = (inverse(cameraView) * ray_eye);
        ray_wor = glm::normalize(ray_wor);
        auto cameraPos = glm::vec3{cameraTransform[3]};
        auto view = registry.view<Transform, Mesh, Name>();
        float lowDist = 100;
        for (auto entity : view) {
            auto meshPos = glm::vec3(renderer->getGlobalTransform(entity)[3]);
            float distance = 0.1f;
            glm::intersectRaySphere(cameraPos, ray_wor, meshPos, 1.0f, distance);

            if (distance < lowDist) {
                logger.info(registry.get<Name>(entity).name + ", distance: " + std::to_string(distance));
                lowDist = distance;
                clickedEntity = entity;
            }
        }
        if (lowDist < 1) return clickedEntity;
    }
    return selectedEntity;
}

void Editor::initSampler() {

    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = 16.0f;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;

    if (vkCreateSampler(renderer->device, &samplerInfo, nullptr, &sampler) != VK_SUCCESS)
        throw std::runtime_error("failed to create texture sampler!");
}

Editor::~Editor() {
    if (!currentFile.empty()) texture.free(renderer->device);
}

void Editor::setStyle() {
    ImGuiStyle &st = ImGui::GetStyle();
    st.FrameBorderSize = 0.0f;
    st.FramePadding = ImVec2(4.0f, 2.0f);
    st.ItemSpacing = ImVec2(8.0f, 2.0f);
    st.WindowBorderSize = 0.0f;
    st.TabBorderSize = 0.0f;
    st.WindowRounding = 0.0f;
    st.ChildRounding = 0.0f;
    st.FrameRounding = 0.0f;
    st.ScrollbarRounding = 0.0f;
    st.GrabRounding = 0.0f;
    st.TabRounding = 0.0f;

    // Setup style
    ImVec4 *colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_DockingPreview] = ImVec4(0.000f, 0.000f, 0.000f, 1.000f);
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.010f, 0.010f, 0.010f, 1.000f);
    colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.53f, 0.53f, 0.53f, 0.46f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 0.53f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.122f, 0.122f, 0.122f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.47f, 0.47f, 0.91f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.55f, 0.55f, 0.62f);
    colors[ImGuiCol_Button] = ImVec4(0.50f, 0.50f, 0.50f, 0.63f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.68f, 0.63f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.26f, 0.26f, 0.63f);
    colors[ImGuiCol_Header] = ImVec4(0.54f, 0.54f, 0.54f, 0.58f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.64f, 0.65f, 0.65f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 0.80f);
    colors[ImGuiCol_Separator] = ImVec4(0.58f, 0.58f, 0.58f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.81f, 0.81f, 0.81f, 0.64f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.87f, 0.87f, 0.87f, 0.53f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.87f, 0.87f, 0.87f, 0.74f);
    colors[ImGuiCol_Tab] = ImVec4(0.01f, 0.01f, 0.01f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.122f, 0.122f, 0.122f, 1.000f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.38f, 0.48f, 0.60f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.68f, 0.68f, 0.68f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.77f, 0.33f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.87f, 0.55f, 0.08f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.47f, 0.60f, 0.76f, 0.47f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.58f, 0.58f, 0.58f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}
