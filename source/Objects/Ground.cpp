# include "Ground.hpp"

Ground::Ground(P2World& world, const Vec2& position, const SizeF& size) : Terrain(world, position, size) {}

void Ground::draw() const
{
	Terrain::draw();

	body.draw(Palette::White.withAlpha(64));
}
