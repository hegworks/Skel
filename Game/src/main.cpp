#include "skelpch.h"
#include "Core/Engine.h"
#include "ExampleGame.h"

int main()
{

    ExampleGame mainGame;
    Engine::GetInstance().Run(mainGame);

    return 0;
}
