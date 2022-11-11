#include <iostream>
#include "Player.h"
#include "Enemy.h"

Player::Player()
{
	bDead = false;
	bNotTakeDamage = false;

	m_MaxHealth = 500;
	m_Health = m_MaxHealth;
	m_Heal = 100;
	m_MeleeDamage = 90;
	m_RangedDamage = 30;
}

void Player::SetStats(int MaxHealth, int Heal, int MeeleDamage, int RangedDamage)
{
	m_MaxHealth = MaxHealth;
	m_Health = m_MaxHealth;
	m_Heal = Heal;
	m_MeleeDamage = MeeleDamage;
	m_RangedDamage = RangedDamage;
}

void Player::Attack(std::vector<std::shared_ptr<Enemy>>& Enemies)
{
	for (int i = Enemies.size() - 1; i >= 0; i--)
	{
		std::cout << "Geralt attacked Enemy " << i + 1 << "  ";

		if (SpecialItems.bSword && SpecialAbilities.bCriticalHit && Probablity() == ESpecialAbility::ESA_CriticalHit) Enemies[i]->DealDamage(CriticalHit());

		else if (SpecialItems.bBow && SpecialAbilities.bRangedAttack && Probablity() == ESpecialAbility::ESA_RangedAttack)
		{
			RangedAttackPower();
			Enemies[i]->DealDamage(m_RangedDamage);
		}
		else
		{
			Enemies[i]->DealDamage(m_MeleeDamage);
			if (SpecialItems.bArmour && SpecialAbilities.bLifeSteal && Probablity() == ESpecialAbility::ESA_LifeSteal) LifeSteal(Enemies[i]);
		}

		if (Enemies[i]->Dead())
		{
			Enemies.erase(Enemies.begin() + i);
			std::cout << "" << std::endl;
			//std::cout << "Geralt cleared Enemy " << i + 1 << std::endl;
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
	if (bNotTakeDamage)
	{
		std::cout << "    Player Did not take any Damage because Player previously Preformed RangedAttack()!" << std::endl;
		bNotTakeDamage = false;
		return;
	}

	if (SpecialItems.bShield && SpecialAbilities.bBlocker && Probablity() == ESpecialAbility::ESA_Blocker) Block();
	else if (!(m_Health <= 0))
	{
		std::cout << "   ||   Damage Done: " << Damage << std::endl;
		std::cout << "" << std::endl;
		m_Health -= Damage;
		if (m_Health <= 0) bDead = true;
	}
}

void Player::IncreaseStats(const ELevels& CurrentLevel)
{
	std::cout << "----Player Stats Increased!----" << std::endl;
	switch (CurrentLevel)
	{
	case 1:
		SetStats(600, 200, 150, 100);
		SpecialItems.bMap = true;

		std::cout << "----Player Recevied the Map!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 2:
		SetStats(700, 300, 200, 150);
		SpecialItems.bSword = true;
		SpecialAbilities.bCriticalHit = true;

		std::cout << "----2nd Special Ability critical Hit Unlocked! - Critical Hit!----" << std::endl;
		std::cout << "----Geralt Received the Swored!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 3:
		SetStats(800, 400, 250, 200);
		SpecialItems.bShield = true;
		SpecialAbilities.bBlocker = true;

		std::cout << "----3rd Special Ability Unlocked! - Blocker!----" << std::endl;
		std::cout << "----Geralt Received the Shield----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 4:
		SetStats(900, 500, 300, 250);
		SpecialItems.bArmour = true;
		SpecialAbilities.bLifeSteal = true;

		std::cout << "----4th Special Ability Unlocked! - Life Steal!----" << std::endl;
		std::cout << "----Geralt Received the Armour!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	case 5:
		SetStats(1000, 600, 350, 300);
		SpecialItems.bBow = true;
		SpecialAbilities.bRangedAttack = true;

		std::cout << "----5th Special Ability Unlocked! - Ranged Attack!----" << std::endl;
		std::cout << "----Geralt Received the Bow!----" << std::endl;
		std::cout << "" << std::endl;
		break;
	default:
		break;
	}
}

bool Player::Dead()
{
	if (bDead)
	{
		std::cout << "--Geralt: I'm dead!--" << std::endl;
		return true;
	}
	else
		return false;
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

void Player::LifeSteal(std::shared_ptr<Enemy>& Enemy)
{
	if (!Enemy->Dead())
	{
		int StealedHealth = Enemy->GetHealth() / 3;
		Enemy->SetHealth(Enemy->GetHealth() - StealedHealth);
		m_Health += StealedHealth; // if geralt steals vitality, health can go greater then MaxHealth of the Geralt!
		std::cout << "" << std::endl;
		std::cout << "Geralt's Armour Stealed the vitality of the Enemy!" << std::endl;
	}
	else
		std::cout << "Enemy Dead, Can't Steal Vitality!" << std::endl;
}

void Player::RangedAttackPower()
{
	bNotTakeDamage = true;
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

