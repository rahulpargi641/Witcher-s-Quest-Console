#include <iostream>
#include "Player.h"
#include "Enemy.h"

Player::Player()
{
	m_IsDead = false;
	m_CanTakeDamage = true;
	m_MaxHealth = 500;
	m_Health = m_MaxHealth;
	m_Heal = 100;
	m_MeleeDamage = 90;
	m_RangedDamage = 30;
}

void Player::SetStats(int maxHealth, int heal, int meeleDamage, int rangedDamage)
{
	m_MaxHealth = maxHealth;
	m_Health = m_MaxHealth;
	m_Heal = heal;
	m_MeleeDamage = meeleDamage;
	m_RangedDamage = rangedDamage;
}

void Player::Attack(std::vector<std::shared_ptr<Enemy>>& enemies)
{
	for (int i = enemies.size() - 1; i >= 0; i--)
	{
		std::cout << "Geralt attacked Enemy " << i + 1 << "  ";

		if (m_SpecialItems.m_HasSword && m_SpecialAbilities.m_HasCriticalHit && Probablity() == ESpecialAbility::ESA_CriticalHit)
		{
			enemies[i]->DealDamage(CriticalHit());
		}
		else if (m_SpecialItems.m_HasBow && m_SpecialAbilities.m_HasRangedAttack && Probablity() == ESpecialAbility::ESA_RangedAttack)
		{
			RangedAttackPower();
			enemies[i]->DealDamage(m_RangedDamage);
		}
		else
		{
			enemies[i]->DealDamage(m_MeleeDamage);
			if (m_SpecialItems.m_HasArmour && m_SpecialAbilities.m_HasLifeSteal && Probablity() == ESpecialAbility::ESA_LifeSteal) 
				LifeSteal(enemies[i]);
		}

		if (enemies[i]->IsDead())
		{
			enemies.erase(enemies.begin() + i);
			std::cout << "" << std::endl;
		}
		break;
	}
	std::cout << "" << std::endl;
}

void Player::Heal()
{
	if (m_Health < m_MaxHealth)
	{
		m_Health += m_Heal;
		if (m_Health > m_MaxHealth) m_Health = m_MaxHealth;
		std::cout << "Geralt Healed" << ", now Health is: " << m_Health << std::endl;
		std::cout << "" << std::endl;
	}
	else
		std::cout << "Geralt's Health is Full!" << std::endl;

}

void Player::DealDamage(int Damage)
{
	if (!m_CanTakeDamage)
	{
		std::cout << "    Player Did not take any Damage because Player previously Preformed RangedAttack()!" << std::endl;
		m_CanTakeDamage = true;
		return;
	}

	if (m_SpecialItems.m_HasShield && m_SpecialAbilities.m_HasBlocker && Probablity() == ESpecialAbility::ESA_Blocker)
	{
		Block();
	}
	else if (m_Health > 0)
	{
		std::cout << "   ||   Damage Done: " << Damage << std::endl << std::endl;
		m_Health -= Damage;
		if (m_Health <= 0)
		{
			m_IsDead = true;
			std::cout << "--Geralt: I'm dead!--" << std::endl;
		}
	}
}

void Player::IncreaseStats(const ELevels currentLevel)
{
	std::cout << "----Player Stats Increased!----" << std::endl;
	switch (currentLevel)
	{
	case 1:
		SetStats(600, 200, 150, 100);
		m_SpecialItems.m_HasMap = true;

		std::cout << "----Player Recevied the Map!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 2:
		SetStats(700, 300, 200, 150);
		m_SpecialItems.m_HasSword = true;
		m_SpecialAbilities.m_HasCriticalHit = true;

		std::cout << "----2nd Special Ability critical Hit Unlocked! - Critical Hit!----" << std::endl;
		std::cout << "----Geralt Received the Swored!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 3:
		SetStats(800, 400, 250, 200);
		m_SpecialItems.m_HasShield = true;
		m_SpecialAbilities.m_HasBlocker = true;

		std::cout << "----3rd Special Ability Unlocked! - Blocker!----" << std::endl;
		std::cout << "----Geralt Received the Shield----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 4:
		SetStats(900, 500, 300, 250);
		m_SpecialItems.m_HasArmour = true;
		m_SpecialAbilities.m_HasLifeSteal = true;

		std::cout << "----4th Special Ability Unlocked! - Life Steal!----" << std::endl;
		std::cout << "----Geralt Received the Armour!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 5:
		SetStats(1000, 600, 350, 300);
		m_SpecialItems.m_HasBow = true;
		m_SpecialAbilities.m_HasRangedAttack = true;

		std::cout << "----5th Special Ability Unlocked! - Ranged Attack!----" << std::endl;
		std::cout << "----Geralt Received the Bow!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	default:
		break;
	}
}

bool Player::IsDead()
{
	return m_IsDead;
}

int Player::CriticalHit()
{
	int CriticalDamage = m_MeleeDamage * 2;
	std::cout << "  ** Critical Hit! **";
	return CriticalDamage;
}

void Player::Block()
{
	std::cout << "   ***  Geralt Used Shield to Block the Attack!  ***" << std::endl;
	std::cout << "" << std::endl;
}

void Player::LifeSteal(std::shared_ptr<Enemy>& enemy)
{
	if (!enemy->IsDead())
	{
		int StealedHealth = enemy->GetHealth() / 3;
		enemy->SetHealth(enemy->GetHealth() - StealedHealth);
		m_Health += StealedHealth; // if geralt steals vitality, health can go greater then MaxHealth of the Geralt!
		std::cout << "" << std::endl;
		std::cout << "Geralt's Armour Stealed the vitality of the Enemy!" << std::endl;
	}
	else
		std::cout << "Enemy Dead, Can't Steal Vitality!" << std::endl;
}

void Player::RangedAttackPower()
{
	m_CanTakeDamage = false;
	std::cout << "" << std::endl;
	std::cout << "Geralt Performed Ranged Attack!" << std::endl;
}

ESpecialAbility Player::Probablity()
{
	srand((unsigned)time(NULL));
	int Value = rand();
	Value = rand() % 100 + 1;  //Generate random number 1 to 100

	if (Value >= 50)
	{
		if (Value <= 75) return ESpecialAbility::ESA_CriticalHit;
		else
			return ESpecialAbility::ESA_Blocker;
	}
	else
	{
		if (Value <= 25) return ESpecialAbility::ESA_LifeSteal;
		else
			return ESpecialAbility::ESA_RangedAttack;
	}
}

