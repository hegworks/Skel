#include "skelpch.h"
#include "Core/Engine.h"
#include "SkelGameBase.h"

int main()
{
	SkelGameBase mainGame;
	Engine::GetInstance().Run(mainGame);

	return 0;
}
