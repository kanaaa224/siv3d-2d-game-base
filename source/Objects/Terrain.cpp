# include "Terrain.hpp"

Terrain::Terrain(P2World& world, const Vec2& position, const SizeF& size) : ObjectBase(world, position)
{
	body = world.createRect(
		P2Static,
		position,
		size,
		P2Material{
			.friction = 0.9
		},
		P2Filter{
			.categoryBits = CollisionCategory::Terrain,
			.maskBits     = CollisionCategory::All
		}
	);
}

void Terrain::draw() const
{
#ifdef _DEBUG
	body.drawFrame();
#endif
}
