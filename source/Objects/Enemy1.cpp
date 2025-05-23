# include "Enemy1.hpp"
# include "../Stages/Stage.hpp"
# include "./Player.hpp"

Enemy1::Enemy1(P2World& world, const Vec2& position) : CharacterBase(world, position), start_position(position)
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
	if (body.getPos().y >= 1000)
	{
		body.setPos(start_position);
		body.setVelocity(Vec2{});
	}
}

void Enemy1::draw() const
{
	body.drawFrame();
}

void Enemy1::onHit(ObjectBase& object)
{
	if (Player* player = dynamic_cast<Player*>(&object))
	{
		if (object.getBody().getPos().y < (body.getPos().y - 100))
		{
			object.getBody().applyLinearImpulse(Vec2{ 0, -300 });

			Stage::GetInstance()->deleteObject(this);
		}
		else
		{
			if (object.getBody().getPos().x < body.getPos().x)
			{
				object.getBody().applyLinearImpulse(Vec2{ -100, -100 });
			}
			else
			{
				object.getBody().applyLinearImpulse(Vec2{ 100, -100 });
			}

			player->addHP(-10);
		}
	}
}

void Enemy1::finalize()
{

}
