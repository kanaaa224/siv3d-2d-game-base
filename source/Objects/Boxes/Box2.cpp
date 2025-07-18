# include "Box2.hpp"

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
	if (body.getPos().y >= (Scene::Height() + 100)) deleteSelf();
}

void Box2::draw() const
{
	TextureAsset(U"Box 2").resized({ 55, 55 }).rotated(body.getAngle()).drawAt(body.getPos());

#ifdef _DEBUG
	body.drawFrame();
#endif
}
