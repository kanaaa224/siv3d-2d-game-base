# pragma once

# include "Terrain.hpp"

class Ceiling : public Terrain
{
public:
	Ceiling(P2World& world, const Vec2& position = { 0, 0 }, const SizeF& size = { 0, 0 });

	void draw() const override;
};
