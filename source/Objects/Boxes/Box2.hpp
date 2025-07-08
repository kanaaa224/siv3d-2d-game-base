# pragma once

# include "../ObjectBase.hpp"

class Box2 : public ObjectBase
{
public:
	Box2(P2World& world, const Vec2& position = { 0, 0 });
	~Box2() = default;

	void update() override;
	void draw() const override;
};
