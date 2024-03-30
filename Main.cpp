#include <iostream>
#include <memory>
#include "GameManager.h"

int main()
{
	std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>();
	gameManager->StartGame();
}

