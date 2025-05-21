# include "Enemy1.hpp"

Enemy1::Enemy1(P2World& world, const Vec2& position) : CharacterBase(world, position)
{
	body = world.createRect(P2Dynamic, position, SizeF{ 75, 100 });

	body.setFixedRotation(true);

	this->initialize();
}

Enemy1::~Enemy1()
{
	this->finalize();
}

void Enemy1::initialize()
{

}

void Enemy1::update()
{

}

void Enemy1::draw() const
{
	body.drawFrame();
}

void Enemy1::finalize()
{

}
