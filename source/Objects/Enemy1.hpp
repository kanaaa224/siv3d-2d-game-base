# pragma once

# include "CharacterBase.hpp"

class Enemy1 : public CharacterBase
{
public:
	Enemy1(P2World& world, const Vec2& position);
	~Enemy1() = default;

	void update() override;
	void draw() const override;

	void onHit(ObjectBase& object) override;

private:
	Vec2 start_position;

	void initialize();
};
