# pragma once

# include "ObjectBase.hpp"

class Blast : public ObjectBase
{
public:
	Blast(P2World& world, const Vec2& position = { 0, 0 }, const SizeF& size = { 100, 100 }, bool player_apply_damage = false, const Milliseconds& life_time = std::chrono::milliseconds{ 1500 });

	void draw() const override;

private:
	void onCollision(ObjectBase& object, const P2Collision& collision) override;

	Effect effect;
};
