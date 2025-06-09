# include "Base.hpp"
# include "../Player.hpp"

EnemyBase::EnemyBase(P2World& world, const Vec2& position) : CharacterBase(world, position), start_position(position)
{
	body = world.createRect(
		P2Dynamic,
		position,
		SizeF { 75, 100 },
		P2Material {},
		P2Filter {
			.categoryBits = CollisionCategory::Enemy,
			.maskBits     = CollisionCategory::All
		}
	);

	body.setFixedRotation(true);

	initialize();
}

void EnemyBase::initialize()
{
	max_hp = 100;

	hp = max_hp;
}

void EnemyBase::update()
{
	if (body.getPos().y >= (Scene::Height() + 100))
	{
		body.setPos(start_position);
		body.setVelocity({ 0, 0 });
	}
}

void EnemyBase::draw() const
{
	body.drawFrame();
}

void EnemyBase::onHit(ObjectBase& object)
{
	if (Player* player = dynamic_cast<Player*>(&object))
	{
		if (object.getBody().getPos().y < (body.getPos().y - 100))
		{
			object.getBody().applyLinearImpulse({ 0, -200 });

			this->applyDamage(25);
		}
		else
		{
			if (object.getBody().getPos().x < body.getPos().x)
			{
				object.getBody().applyLinearImpulse({ -100, -100 });
			}
			else
			{
				object.getBody().applyLinearImpulse({ 100, -100 });
			}

			player->applyDamage(10);
		}
	}
}
