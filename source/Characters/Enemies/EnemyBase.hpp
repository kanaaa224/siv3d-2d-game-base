# pragma once

# include "../CharacterBase.hpp"
# include "../../UI/HPBar.hpp"

# define ENEMY_MAX_HP 100

class EnemyBase : public CharacterBase
{
public:
	EnemyBase(P2World& world, const Vec2& position = { 0, 0 });

	virtual void update() override;
	virtual void draw() const override;

	void onDamaged(float amount) override;

	void setPlayerPosition(const Vec2& position = { 0, 0 }) { player_position = position; }

protected:
	Vec2 current_position;
	Vec2 start_position;
	Vec2 player_position;

	HPBar hpBar{ ENEMY_MAX_HP };

	bool damaged;

	Effect effect;

	virtual void initialize();
};
