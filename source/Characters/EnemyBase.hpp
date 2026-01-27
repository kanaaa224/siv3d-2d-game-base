# pragma once

# include "CharacterBase.hpp"
# include "../UI/HPBar.hpp"

class EnemyBase : public CharacterBase
{
public:
	EnemyBase(P2World& world, const Vec2& position = { 0, 0 });

	virtual void update() override;
	virtual void draw() const override;

	void onDamaged(int32 amount) override;

	void setPlayerPosition(const Vec2& position = { 0, 0 }) { player_position = position; }

protected:
	Vec2 current_position;
	Vec2 start_position;
	Vec2 player_position;

	HPBar hpBar{ DEFAULT_HP };

	bool damaged;

	Effect effect;

	int32 speed;
};
