# include "Ceiling.hpp"

Ceiling::Ceiling(P2World& world, const Vec2& position, const SizeF& size) : Terrain(world, position, size) {}

void Ceiling::draw() const
{
	Terrain::draw();

	body.draw(Palette::White.withAlpha(64));
}
