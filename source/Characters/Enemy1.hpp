# pragma once

# include "EnemyBase.hpp"

class Enemy1 : public EnemyBase
{
public:
	Enemy1(P2World& world, const Vec2& position = { 0, 0 });

	void update() override;
	void draw() const override;

private:
	void onCollision(ObjectBase& object, const P2Collision& collision) override;
};
