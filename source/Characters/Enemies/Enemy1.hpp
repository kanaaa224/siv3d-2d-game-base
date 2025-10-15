# pragma once

# include "EnemyBase.hpp"

class Enemy1 : public EnemyBase
{
public:
	Enemy1(P2World& world, const Vec2& position = { 0, 0 });

	virtual void update() override;
	virtual void draw() const override;

	virtual void onHit(ObjectBase& object, const P2Collision& collision) override;
};
