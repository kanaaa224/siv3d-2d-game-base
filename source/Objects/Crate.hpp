# pragma once

# include "ObjectBase.hpp"

class Crate : public ObjectBase
{
public:
	Crate(P2World& world, const Vec2& position = { 0, 0 }, bool playerPassThrough = false);

	void update() override;
	void draw() const override;
};
