#pragma once

#include "System.h"

class SystemsManager {
private:
    System **systems = new System *[10];
    int count = 0;

public:
    void updateSystems(const float& delta);

    void attachSystem(System *system);

    void detachSystem(System *system);

    ~SystemsManager();
};
