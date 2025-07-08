# include "Enemy1.hpp"
# include "../Player.hpp"

Enemy1::Enemy1(P2World& world, const Vec2& position) : EnemyBase(world, position)
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
}

void Enemy1::onHit(ObjectBase& object, const P2Collision& collision)
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
