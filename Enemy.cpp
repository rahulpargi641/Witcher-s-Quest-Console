#include <iostream>
#include "Enemy.h"
#include "Player.h"

int Enemy::s_EnemyCount = 0;

Enemy::Enemy()
{
	Enemy::s_EnemyCount++;
	m_IsDead = false;
	m_Health = 100;
	m_Damage = 50;
	m_Defese = 50;
}

void Enemy::Attack(std::shared_ptr<Player>& player)
{
	player->DealDamage(m_Damage);
}

bool Enemy::Defended()
{
	srand((unsigned) time(NULL));
	int Defense = rand();
	Defense = rand() % 100 + 1;  // Generate random number 1 to 100
	if (Defense <= 20) //20% probability 
	{
		std::cout << "" << std::endl;
		std::cout << "---Enemy Defended!--- No Damage Done!" << std::endl;
		return true;
	}
	else
		return false;
}

void Enemy::DealDamage(int damage)
{
	if (m_Health > 0)
	{
		if (Defended()) return;

		std::cout << "   ||   Damage Done: " << damage << std::endl;
		m_Health -= damage;
		if (m_Health <= 0)
		{
			s_EnemyCount--;
			m_IsDead = true;
			std::cout << "--Enemy: now, I'm dead :(-----" << std::endl;
		}
	}
}

bool Enemy::IsDead() const
{
	if (m_IsDead) return true;
	else 
		return false;
}




