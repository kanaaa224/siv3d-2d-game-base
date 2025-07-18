# pragma once

# include "EnemyBase.hpp"

class Enemy2 : public EnemyBase
{
public:
	Enemy2(P2World& world, const Vec2& position = { 0, 0 });
	~Enemy2() = default;

	virtual void draw() const override;

	virtual void onHit(ObjectBase& object, const P2Collision& collision) override;
};
