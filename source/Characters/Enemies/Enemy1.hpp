# pragma once

# include "EnemyBase.hpp"

class Enemy1 : public EnemyBase
{
public:
	Enemy1(P2World& world, const Vec2& position = { 0, 0 });
	~Enemy1() = default;

	virtual void draw() const override;

	virtual void onHit(ObjectBase& object, const P2Collision& collision) override;

private:
	Effect effect;
};
