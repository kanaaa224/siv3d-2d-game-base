# pragma once

# include "ObjectBase.hpp"

class Bullet : public ObjectBase
{
public:
	Bullet(P2World& world, const Vec2& position = { 0, 0 }, const Vec2& direction = { 0, 0 }, double size = 4.0);

	void update() override;
	void draw() const override;

	virtual void onHit(ObjectBase& object, const P2Collision& collision) override;

private:
	Effect effect;

	Vec2 current_position;

	bool hit;
};
