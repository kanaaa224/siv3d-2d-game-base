# pragma once

# include "Terrain.hpp"

class Wall : public Terrain
{
public:
	Wall(P2World& world, const Vec2& position = { 0, 0 }, const SizeF& size = { 0, 0 });

	void draw() const override;
};
