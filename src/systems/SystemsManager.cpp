#include "SystemsManager.h"
namespace Engine {
    void SystemsManager::attachSystem(System *system) {
        if (count == 10) return;
        systems[count] = system;
        count++;
    }

    void SystemsManager::detachSystem(System *system) {

    }

    void SystemsManager::updateSystems(const float &delta) {
        for (int i = 0; i < count; ++i)
            systems[i]->update(delta);
    }

    SystemsManager::~SystemsManager() {
        delete[] systems;
    }

}