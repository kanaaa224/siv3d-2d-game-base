# pragma once

# include "ObjectBase.hpp"

class Ground : public ObjectBase
{
public:
	Ground(P2World& world, const Vec2& position = { 0, 0 }, const SizeF& size = { 0, 0 });

	void draw() const override;
};
