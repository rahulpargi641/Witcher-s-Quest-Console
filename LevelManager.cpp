#include <iostream>
#include <memory>
#include "LevelManager.h"

LevelManager::LevelManager()
{
	m_Player = std::make_unique<Player>();
}

void LevelManager::CreateLevel(int currentLevel)
{
	SetCurrentLevel(currentLevel);
	CreateEnemies(currentLevel);
}

void LevelManager::CreateEnemies(int currentLevel)
{
	if (currentLevel != ELevels::EL_BossLevel)
	{
		for (int i = 0; i < currentLevel; i++)
		{
			std::shared_ptr<Enemy> Enemy = std::make_unique<class Enemy>();
			m_Enemies.push_back(Enemy);
		}
		std::cout << "" << std::endl;
	}
	else
	{
		std::shared_ptr<Murloc> m_Murloc = std::make_unique<class Murloc>();
		m_Enemies.push_back(m_Murloc);
		std::cout << "Boss Level!" << std::endl;
	}
}

void LevelManager::SetCurrentLevel(int currentLevel)
{
	switch (currentLevel)
	{
	case 1:
		m_CurrentLevel = ELevels::EL_First;
		break;
	case 2:
		m_CurrentLevel = ELevels::EL_Second;
		break;
	case 3:
		m_CurrentLevel = ELevels::EL_Third;
		break;
	case 4:
		m_CurrentLevel = ELevels::EL_Fourth;
		break;
	case 5:
		m_CurrentLevel = ELevels::EL_Fifth;
		break;
	case 6:
		m_CurrentLevel = ELevels::EL_BossLevel;
	default:
		break;
	}
}

void LevelManager::ProcessLevelComplete()
{
	if (m_CurrentLevel == ELevels::EL_BossLevel) return;

	m_Player->IncreaseStats(m_CurrentLevel);
}

void LevelManager::ShowGameInfo()
{
	std::cout << "" << std::endl;
	std::cout << "GAME INFO:" << std::endl;
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "Current Game Level: " << (int)m_CurrentLevel << std::endl;
	std::cout << "Geralt's Health: " << m_Player->GetHealth();
	std::cout << "   |   Meele Damage: " << m_Player->GetMeeleDamage() << "   |   Ranged Damage: " << m_Player->GetRangedDamage() << std::endl;
	std::cout << "No. of Enemies: " << m_Enemies.size()<< "   |   ";

		for (int i = 0; i < m_Enemies.size(); i++)
		std::cout << "Enemy " << i + 1 << " Health: " << m_Enemies[i]->GetHealth() << "   ||   ";
		std::cout << " " << std::endl;
	std::cout << "-----------------------------------------------------------------" << std::endl;
}






