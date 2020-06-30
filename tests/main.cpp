#include <vector>
#include "iostream"

#define TYPES
#define SHOW_EDITOR(name)
enum class Type {
    Vec3, Color, Mat4, Quat, Float, Integer
};


struct Position {
    float x;
    float y;
    float color[4];
};

std::vector<Type> getMembers() {
    std::vector<Type> members{};
    members.push_back(Type::Float);
    members.push_back(Type::Float);
    members.push_back(Type::Color);
    return members;
};
struct Scale {
    float x;
    float y;
};

template<typename T>
void paraseType(T type) {
    std::cout << typeid(type).name() << std::endl;
    uint32_t offset = 0;
    for (Type member: getMembers()) {
        void *t = reinterpret_cast<char *>(&type + offset);
        if (member == Type::Float) {
            auto *meh = reinterpret_cast<float *>(t);
            std::cout << "Float: " << *meh << std::endl;
            offset += sizeof(float);
        } else if (member == Type::Integer) {
            auto *meh = reinterpret_cast<int *>(t);
            std::cout << "Integer: " << *meh << std::endl;
            offset += sizeof(int);
        } else if (member == Type::Color) {
            auto *meh = reinterpret_cast<float *>(t);
            std::cout << "Color: " << meh[0] << ", " << meh[1] << ", " << meh[2] << ", " << meh[3] << std::endl;
            offset += sizeof(float[4]);
        }
    }
}

int main() {
    paraseType(Position{154.f, 44.f, {0.1f, 0.2f, 0.3f, 1.0f}});
}