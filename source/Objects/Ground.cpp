# include "Ground.hpp"

Ground::Ground(P2World& world, const Vec2& position, const SizeF& size) : ObjectBase(world, position)
{
	body = world.createRect(
		P2Static,
		position,
		size,
		P2Material{
			.friction = 0.9
		},
		P2Filter{
			.categoryBits = CollisionCategory::Ground,
			.maskBits     = CollisionCategory::All
		}
	);
}

void Ground::draw() const
{
	body.draw();

#ifdef _DEBUG
	body.drawFrame();
#endif
}
