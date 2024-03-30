#pragma once
#include <string>
#include <vector>
#include "GameManager.h"

class Enemy;

enum class ESpecialAbility : unsigned char
{
	ESA_CriticalHit = 1, ESA_Blocker, ESA_LifeSteal, ESA_RangedAttack
};

struct SpecialItems
{
	bool m_HasMap = false;
	bool m_HasSword = false;
	bool m_HasShield = false;
	bool m_HasArmour = false;
	bool m_HasBow = false;
};

struct SpecialAbilities
{
	bool m_HasCriticalHit = false;
	bool m_HasBlocker = false;
	bool m_HasLifeSteal = false;
	bool m_HasRangedAttack = false;
};

class Player
{
private:
	SpecialItems m_SpecialItems;
	SpecialAbilities m_SpecialAbilities;

	const std::string m_Name = "Geralt";

	bool m_IsDead;
	bool m_CanTakeDamage;
	int m_MaxHealth;
	int m_Health;
	unsigned int m_Heal;
	unsigned int m_MeleeDamage;
	unsigned int m_RangedDamage;

private:
	int CriticalHit();
	void Block();
	void LifeSteal(std::shared_ptr<Enemy>& enemy);
	void RangedAttackPower();
	ESpecialAbility Probablity();
	void SetStats(int maxHealth, int heal, int meeleDamage, int rangedDamage);

public:
	Player();
	void Attack(std::vector<std::shared_ptr<Enemy>>& enemies);
	void Heal();
	void DealDamage(int damage);
	bool IsDead();
	void IncreaseStats(const ELevels currentLevel);
	inline int GetHealth() const { return m_Health; }
	inline int GetMeeleDamage() const { return m_MeleeDamage; }
	inline int GetRangedDamage() const { return m_RangedDamage; }
};

