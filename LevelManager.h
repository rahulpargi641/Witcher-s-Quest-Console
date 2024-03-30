#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Murloc.h"
#include "GameManager.h"

enum ELevels : unsigned char { EL_First = 1, EL_Second, EL_Third, EL_Fourth, EL_Fifth, EL_BossLevel, EL_Default = 0 };

class LevelManager
{
private:
	const int Max_Levels = 6;

	ELevels m_CurrentLevel;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Enemy>> m_Enemies;

public:

	LevelManager();

	inline std::shared_ptr<Player>& GetPlayer() { return m_Player; }
	inline std::vector<std::shared_ptr<Enemy>>& GetEnemies() { return m_Enemies; }
	inline int GetMaxLevelNo() const { return Max_Levels; }

	void CreateLevel(int currentLevel);
	void CreateEnemies(int currentLevel);
	void SetCurrentLevel(int level);
	void ProcessLevelComplete();
	void ShowGameInfo();
};
