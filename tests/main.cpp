#include "iostream"
#include "entt/entity/registry.hpp"

struct Postion {
    float x;
    float y;
};

struct Scale {
    float x;
    float y;
};

int main() {
    entt::registry registry;
    std::cout << "Hello Test" << std::endl;

    auto entity = registry.create();

    registry.emplace<Postion>(entity, 0.f, 0.f);

    auto &scale = registry.emplace<Scale>(entity);

    registry.destroy(entity);

}