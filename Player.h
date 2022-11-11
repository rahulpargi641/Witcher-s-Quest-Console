#pragma once
#include <string>
#include <vector>
#include "Main.h"

class Enemy;

enum class ESpecialAbility : unsigned char
{
	ESA_CriticalHit = 1, ESA_Blocker, ESA_LifeSteal, ESA_RangedAttack
};

struct SpecialItems
{
	bool bMap = false;
	bool bSword = false;
	bool bShield = false;
	bool bArmour = false;
	bool bBow = false;
};

struct SpecialAbilities
{
	bool bCriticalHit = false;
	bool bBlocker = false;
	bool bLifeSteal = false;
	bool bRangedAttack = false;
};

class Player
{
private:
	bool bDead;
	bool bNotTakeDamage;

	SpecialItems SpecialItems;
	SpecialAbilities SpecialAbilities;
	const std::string m_Name = "Geralt";
	int m_MaxHealth;
	int m_Health;
	int m_Heal;
	unsigned int m_MeleeDamage;
	unsigned int m_RangedDamage;

private:
	int CriticalHit();
	void Block();
	void LifeSteal(std::shared_ptr<Enemy>& Enemy);
	void RangedAttackPower();
	ESpecialAbility Probablity();
	void SetStats(int MaxHealth, int Heal, int MeeleDamage, int RangedDamage);

public:
	Player();
	void Attack(std::vector<std::shared_ptr<Enemy>>& Enemies);
	void Heal();
	void DealDamage(int Damage);
	bool Dead();
	void IncreaseStats(const ELevels& CurrentLevel);
	inline int GetHealth() const { return m_Health; }
	inline int GetMeeleDamage() const { return m_MeleeDamage; }
	inline int GetRangedDamage() const { return m_RangedDamage; }
};

