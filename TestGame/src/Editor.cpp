#include "Editor.h"
#include <filesystem>
#include <components/Name.h>
#include <components/Mesh.h>
#include <components/Transform.h>
#include <components/Relationship.h>

using namespace Engine;
void Editor::draw() {
    ImGui::Begin("Hierarchy");

    auto nameView = registry.view<Name>();
    for (auto entity: nameView) {
        auto &name = nameView.get<Name>(entity);
        static bool closable_group = true;

        if (ImGui::CollapsingHeader((name.name + ": " + std::to_string((uint32_t) entity)).c_str(),
                                    &closable_group)) {
            if (registry.has<Transform>(entity)) {
                auto &t = registry.get<Transform>(entity);
                if (ImGui::TreeNode(("Transform##" + name.name).c_str())) {
                    ImGui::InputFloat3(("Location##" + name.name).c_str(), &t.location.x);
                    ImGui::InputFloat3(("Scale##" + name.name).c_str(), &t.scale.x);
                    ImGui::InputFloat4(("Rotation##" + name.name).c_str(), &t.rotation.x);
                    t.dirty = true;
                    ImGui::TreePop();
                    ImGui::Separator();
                }
            }
            if (registry.has<Mesh>(entity)) {
                auto &mesh = registry.get<Mesh>(entity);
                if (ImGui::TreeNode(("Colors##" + name.name).c_str())) {
                    for (int i = 0; i < mesh.attributes.size(); i++)
                        ImGui::ColorEdit4(("Color " + std::to_string(i) + "##" + name.name).c_str(),
                                          &mesh.attributes[i].material.color.x);
                    ImGui::TreePop();
                    ImGui::Separator();
                }
            }
            if (registry.has<Relationship>(entity)) {
                auto &relation = registry.get<Relationship>(entity);
                ImGui::InputScalar(("Parent##" + name.name).c_str(), ImGuiDataType_U32, &relation.parent);
            }
            //if (registry.has<Car>(entity)) {
            //    auto &car = registry.get<Car>(entity);
            //    ImGui::InputFloat(("speed##" + name.name).c_str(), &car.speed);
            //}

        }
    }
    ImGui::End();

    ImGui::Begin("Assets");

    directoryContent(".\\data");

    ImGui::End();
}

void Editor::directoryContent(std::string path) {
    ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            if (ImGui::TreeNode(getFileName(entry.path().string()).c_str())) {
                directoryContent(entry.path().string());
                ImGui::TreePop();
            }
        } else ImGui::TreeNodeEx("Object", flags, "%s", getFileName(entry.path().string()).c_str());
    }
}

std::string Editor::getFileName(const std::string &path) {
    return path.substr(path.find_last_of('\\') + 1);
}

Editor::Editor(entt::registry &registry) : registry{registry} {

}
