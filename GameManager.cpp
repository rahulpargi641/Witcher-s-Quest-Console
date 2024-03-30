#include <iostream>
#include "GameManager.h"

GameManager::GameManager()
{
	m_IsGameComplete = false;
	m_IsLevelComplete = false;
	m_LevelManager = std::make_unique<LevelManager>();
	m_Player = m_LevelManager->GetPlayer();
	m_Enemies = m_LevelManager->GetEnemies();
	m_MaxLevelNo = m_LevelManager->GetMaxLevelNo();
}

void GameManager::StartGame()
{
	std::cout << "Text Based RPG Adventure!" << std::endl << std::endl;

	while (!m_IsGameComplete)
        RunLevels();
}

void GameManager::RunLevels()
{
    for (int i = 1; i < m_MaxLevelNo + 1; i++)
    {
        LoadLevel(i);
        RunLevel(i);
    }

    std::cout << "Game Over!" << std::endl;
}

void GameManager::LoadLevel(int levelNo)
{
    std::cout << "Level " << levelNo << " Loaded!" << std::endl;
    m_LevelManager->CreateLevel(levelNo);
    m_IsLevelComplete = false;
}

void GameManager::RunLevel(int currentLevel)
{
	m_CurrentTurn = ETurn::ET_Player;

    while (!m_IsLevelComplete && !m_Player->IsDead())
    {
        if (m_CurrentTurn == ETurn::ET_Player)
        {
			ProcessPlayerTurn();
			SwitchTurn();
            ProcessIfEnemiesDead(currentLevel);
        }
        else
        {
            ProcessEnemyAITurn();
			SwitchTurn();
        }
    }
}

void GameManager::ProcessPlayerTurn()
{
	char Input;
	m_LevelManager->ShowGameInfo();
	std::cout << "" << std::endl;
	std::cout << "Geralt's Turn!      ||     ";
	std::cout << "Press 'A' to Attack, Press 'H' to Heal" << std::endl;

	do
	{
		std::cin >> Input;
		if (Input == 'A' || Input == 'a')
		{
			std::system("cls");
			std::cout << "" << std::endl;
			m_Player->Attack(m_Enemies);
			break;
		}
		else if (Input == 'H' || Input == 'h')
		{
			std::system("cls");
			std::cout << "" << std::endl;
			m_Player->Heal();
			break;
		}
		else
		{
			std::cout << "" << std::endl;
			std::cout << "Wrong Input, Press 'A' or Press 'H' " << std::endl;
		}

	} while (!(Input == 'A' || Input == 'H'));
}

void GameManager::ProcessEnemyAITurn()
{
	std::cout << "" << std::endl;
	std::cout << "Enemy AI playing....." << std::endl;

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		std::cout << "Enemy " << i + 1 << " Attacked Geralt!";
		m_Enemies[i]->Attack(m_Player);
	}
	std::cout << "" << std::endl;
}

void GameManager::SwitchTurn()
{
	m_CurrentTurn = (m_CurrentTurn == ETurn::ET_Player) ? ETurn::ET_AIEnemy : ETurn::ET_Player;
}

void GameManager::ProcessIfEnemiesDead(int currentLevel)
{
	if (currentLevel == m_MaxLevelNo)
	{
		m_IsGameComplete = true;
		return;
	}

	if (m_Enemies.empty())
	{
		m_LevelManager->ProcessLevelComplete();
		m_IsLevelComplete = true;

		std::cout << "All Enemies are dead, Loading Next Level........" << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl << std::endl;
	}
}