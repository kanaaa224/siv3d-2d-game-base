# include "Wall.hpp"

Wall::Wall(P2World& world, const Vec2& position, const SizeF& size) : Terrain(world, position, size) {}

void Wall::draw() const
{
	Terrain::draw();

	body.draw(Palette::White.withAlpha(64));
}
