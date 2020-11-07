#include "Game.h"
#include "components/Car.h"
#include "systems/EntitySystem.h"
#include <logger/TerminalLogger.h>

using namespace Engine;

Game::Game() : Application("Editor") {}

void Game::init() {
    entt::entity sky = renderer->addModel("data/sky.glb");
    //registry.get<Mesh>(sky).attributes[0].material.useColor=1;
    systemsManager->attachSystem(new EntitySystem(registry));
    editor = new Editor(registry, dynamic_cast<VkRenderer *>(renderer));
    editor->init();
    ui->widgets.push_back(editor);
    renderer->uploadData();
}

Game::~Game() {
    delete editor;
}
