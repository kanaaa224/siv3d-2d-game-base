# pragma once

# include "../Base.hpp"

class Box2 : public ObjectBase
{
public:
	Box2(P2World& world, const Vec2& position);
	~Box2() = default;

	void update() override;
	void draw() const override;
};
