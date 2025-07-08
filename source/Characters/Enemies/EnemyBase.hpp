# pragma once

# include "../CharacterBase.hpp"

# define ENEMY_MAX_HP 100

class EnemyBase : public CharacterBase
{
public:
	EnemyBase(P2World& world, const Vec2& position = { 0, 0 });
	~EnemyBase() = default;

	virtual void update() override;
	virtual void draw() const override;

private:
	Vec2 start_position;

	virtual void initialize();
};
