#include "components/Car.h"
#include "systems/EntitySystem.h"
#include "Game.h"
#include "Editor.h"

using namespace Engine;

void Game::init() {
    renderer->addModel("data/models/test2.glb");
    entt::entity entity = renderer->addModel("data/models/test.glb");
    registry.emplace<Car>(entity, Car{0.5f});
    entt::entity entity1 = renderer->addModel("data/models/test3.glb");
    registry.emplace<Car>(entity1, Car{0.45f});
    entt::entity entity2 = renderer->addModel("data/models/test4.glb");
    registry.emplace<Car>(entity2, Car{0.4f});
    systemsManager->attachSystem(new EntitySystem(registry));
    auto *editor = new Editor(registry);
    ui->widgets.push_back(editor);
    renderer->uploadData();
}
