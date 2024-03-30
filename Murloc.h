#pragma once
#include "Enemy.h"

enum class EAttack: unsigned char { EA_GroundDash, EA_SpeedDash };

class Murloc : public Enemy
{
public:
	Murloc();

private:
	void Attack(std::shared_ptr<Player>& player) override;
	void DealDamage(int damage) override;
	int GroundSlashDamage();
	int SpeedDashDamage();
	void HealthRegeneration();
	EAttack GetRandomAttack();
};

