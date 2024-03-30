#pragma once
#include <memory>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "LevelManager.h"

enum class ETurn : unsigned char { ET_Player, ET_AIEnemy };

class GameManager
{
private:
    std::unique_ptr<LevelManager> m_LevelManager;
    std::shared_ptr<Player> m_Player;
    std::vector<std::shared_ptr<Enemy>> m_Enemies;

    bool m_IsGameComplete;
    bool m_IsLevelComplete;
    ETurn m_CurrentTurn;
    int m_MaxLevelNo;

public:
    GameManager();
    void StartGame();
    void LoadLevel(int levelNo);
    void RunLevels();
    void RunLevel(int currentLevel);
    void ProcessPlayerTurn();
    void ProcessEnemyAITurn();
    void ProcessIfEnemiesDead(int currentLevel);
    void SwitchTurn();
};













