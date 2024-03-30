#pragma once
#include <memory>

class Player;

class Enemy
{
private:
	static int s_EnemyCount;
protected:
	bool m_IsDead;
	int m_Health;
	int m_Damage;
	int m_Defese;

protected:
	virtual bool Defended(); 
	
public:
	Enemy();
	virtual void Attack(std::shared_ptr<Player>& player);
	virtual void DealDamage(int damage);
	virtual bool IsDead() const;
	inline int GetHealth() const { return m_Health; }
	inline void SetHealth(int health) { m_Health = health; }
	inline int GetDamage() const { return m_Damage; }
};

