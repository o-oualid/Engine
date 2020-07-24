#include <logger/TerminalLogger.h>
#include "components/Car.h"
#include "systems/EntitySystem.h"
#include "Game.h"

using namespace Engine;

Game::Game():Application("Editor"){}

void Game::init() {
    renderer->addModel("data/models/cars/race.glb");
    systemsManager->attachSystem(new EntitySystem(registry));
    editor = new Editor(registry, dynamic_cast<VkRenderer *>(renderer));
    editor->init();
    ui->widgets.push_back(editor);
    renderer->uploadData();
}

Game::~Game() {
    delete editor;
}
