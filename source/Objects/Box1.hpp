# pragma once

# include "Base.hpp"

class Box1 : public ObjectBase
{
public:
	Box1(P2World& world, const Vec2& position);
	~Box1() = default;

	void update() override;
	void draw() const override;
};
