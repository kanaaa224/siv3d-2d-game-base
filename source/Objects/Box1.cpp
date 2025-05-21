# include "Box1.hpp"

Box1::Box1(P2World& world, const Vec2& position) : ObjectBase(world, position)
{
	body = world.createRect(P2Dynamic, position, SizeF{ 50, 50 });

	this->initialize();
}

Box1::~Box1()
{
	this->finalize();
}

void Box1::initialize()
{

}

void Box1::update()
{

}

void Box1::draw() const
{
	body.drawFrame();
}

void Box1::finalize()
{

}
