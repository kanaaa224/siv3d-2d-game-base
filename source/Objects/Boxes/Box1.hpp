# pragma once

# include "../ObjectBase.hpp"

class Box1 : public ObjectBase
{
public:
	Box1(P2World& world, const Vec2& position = { 0, 0 });

	void update() override;
	void draw() const override;
};
