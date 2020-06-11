#pragma once
namespace Engine {
    class System {
    public:
        virtual void update(const float &delta) = 0;
    };
}