# pragma once

# include "Terrain.hpp"

class Ground : public Terrain
{
public:
	Ground(P2World& world, const Vec2& position = { 0, 0 }, const SizeF& size = { 0, 0 });

	void draw() const override;
};
