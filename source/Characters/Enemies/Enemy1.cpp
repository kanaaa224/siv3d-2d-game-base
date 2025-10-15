# include "Enemy1.hpp"
# include "../Player.hpp"

Enemy1::Enemy1(P2World& world, const Vec2& position) : EnemyBase(world, position)
{
	SizeF size{ 75, 100 };

	body = world.createRect(
		P2Dynamic,
		position,
		size,
		P2Material{},
		P2Filter{
			.categoryBits = CollisionCategory::Enemy,
			.maskBits     = CollisionCategory::All
		}
	);

	body.setFixedRotation(true);
}

void Enemy1::update()
{
	EnemyBase::update();

	if (Abs(player_position.x - body.getPos().x) <= Scene::Width() / 2) body.setVelocity((player_position - current_position).normalized() * 50);
}

void Enemy1::draw() const
{
	TextureAsset(U"Enemy 1").resized({ 105, 105 }).rotated(body.getAngle()).drawAt(body.getPos(), damaged ? ColorF{ 1.0, 0.25, 0.25, 0.5 } : ColorF{ 1.0 });

	EnemyBase::draw();
}

void Enemy1::onHit(ObjectBase& object, const P2Collision& collision)
{
	if (Player* player = dynamic_cast<Player*>(&object))
	{
		if (Abs((object.getBody().getPos().y + 50) - collision.contact(0).point.y) < 10.0)
		{
			object.getBody().applyLinearImpulse({ 0, -100 });
		}
		else
		{
			object.getBody().applyLinearImpulse({ object.getBody().getPos().x < body.getPos().x ? -100 : 100, -50 });

			player->applyDamage(10);
		}
	}
}
