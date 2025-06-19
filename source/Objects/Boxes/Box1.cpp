# include "Box1.hpp"

Box1::Box1(P2World& world, const Vec2& position) : ObjectBase(world, position)
{
	body = world.createRect(
		P2Dynamic,
		position,
		SizeF { 50, 50 },
		P2Material {},
		P2Filter {
			.categoryBits = CollisionCategory::Box1,
			.maskBits     = CollisionCategory::All
		}
	);
}

void Box1::update()
{
	if (body.getPos().y >= (Scene::Height() + 100)) deleteSelf();
}

void Box1::draw() const
{
	body.drawFrame();
}
