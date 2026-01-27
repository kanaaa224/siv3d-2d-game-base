# pragma once

# include "ObjectBase.hpp"

class Terrain : public ObjectBase
{
public:
	Terrain(P2World& world, const Vec2& position = { 0, 0 }, const SizeF& size = { 0, 0 });

	void draw() const override;
};
