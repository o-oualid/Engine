#include <Application.h>
#include "Editor.h"

class Game : public Engine::Application {
private:
    Editor *editor;
public:
    Game();
    void init() override;

    ~Game();
};