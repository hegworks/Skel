#include "skelpch.h"
#include "Core/Engine.h"
#include "UpgradeTree.h"

int main()
{
	UpgradeTree mainGame;
	Engine::GetInstance().Run(mainGame);

	return 0;
}
