# include "Box1.hpp"

Box1::Box1(P2World& world, const Vec2& position) : ObjectBase(world, position)
{
	body = world.createRect(P2Dynamic, position, SizeF{ 50, 50 });
}

void Box1::update()
{
	if (body.getPos().y >= 1000) deleteSelf();
}

void Box1::draw() const
{
	body.drawFrame();
}
