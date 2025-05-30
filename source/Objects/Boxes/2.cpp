# include "2.hpp"

Box2::Box2(P2World& world, const Vec2& position) : ObjectBase(world, position)
{
	body = world.createRect(
		P2Dynamic,
		position,
		SizeF { 50, 50 },
		P2Material {},
		P2Filter {
			.categoryBits = CollisionCategory::Box2,
			.maskBits     = CollisionCategory::All
		}
	);
}

void Box2::update()
{
	if (body.getPos().y >= 1000) deleteSelf();
}

void Box2::draw() const
{
	body.drawFrame();
}
