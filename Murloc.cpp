#include <iostream>
#include "Murloc.h"
#include "Player.h"

Murloc::Murloc()
{
	m_IsDead = false;
	m_Health = 2000;
	m_Damage = 200;
	m_Defese = 200;
	std::cout << "Murlocs : Finally the worthy opponent, I can use my Full Power!" << std::endl;
}

void Murloc::Attack(std::shared_ptr<Player>& player)
{
	if (GetRandomAttack() == EAttack::EA_GroundDash)
		player->DealDamage(GroundSlashDamage());
	else if (GetRandomAttack() == EAttack::EA_SpeedDash) 
		player->DealDamage(SpeedDashDamage());
	else
		player->DealDamage(m_Damage);
}

void Murloc::DealDamage(int damage)
{
	if (!(m_Health <= 0))
	{
		if (Defended()) return;

		std::cout << "   ||   Damage Done: " << damage << std::endl;
		m_Health -= damage;
		if (m_Health <= 0)
		{
			std::cout << "" << std::endl;
			std::cout << "--Murloc: now, I'm dead! , You are indeed The Strongest!--" << std::endl;
			m_IsDead = true;
		}
	}
}

int Murloc::GroundSlashDamage()
{
	int Damage = 1.5 * m_Damage;
	std::cout << "   --Ground Dash Attack!--   ";
	return Damage;
}

int Murloc::SpeedDashDamage()
{
	int Damage = 2 * m_Damage;
	std::cout << "   --SpeedDash Attack!--   ";
	return Damage;
}

void Murloc::HealthRegeneration()
{
	std::cout << "can be Implemented later with async!" << std::endl;
}

EAttack Murloc::GetRandomAttack()
{
	srand((unsigned)time(NULL));
	int Value = rand();
	Value = rand() % 100 + 1;

	if (Value >= 50) return EAttack::EA_GroundDash;
	else
		return EAttack::EA_SpeedDash;
}


