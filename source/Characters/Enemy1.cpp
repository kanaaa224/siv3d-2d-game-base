# include "Enemy1.hpp"
# include "Player.hpp"

Enemy1::Enemy1(P2World& world, const Vec2& position) : EnemyBase(world, position)
{
	SizeF size{ 50, 75 };

	body = world.createRect(
		P2Dynamic,
		position,
		size,
		P2Material{},
		P2Filter{
			.categoryBits = CollisionCategory::Enemy,
			.maskBits     = CollisionCategory::All & ~CollisionCategory::Scaffold
		}
	);

	body.setFixedRotation(true);
	body.setGravityScale(0.0);

	speed = Random(50, 70);
}

void Enemy1::update()
{
	EnemyBase::update();

	if (!damaged)
	{
		if (Abs(player_position.x - current_position.x) <= Scene::Width() / 2) body.setVelocity((player_position - current_position).normalized() * speed);
	}
}

void Enemy1::draw() const
{
	if (body) TextureAsset(U"Enemy 1").resized({ 105, 105 }).rotated(body.getAngle()).drawAt(current_position, damaged ? ColorF{ 1.0, 0.25, 0.25, 0.5 } : ColorF{ 1.0 });

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
			object.getBody().applyLinearImpulse({ object.getBody().getPos().x < current_position.x ? -100 : 100, Random(-10, 10) });

			player->applyDamage(Random(1, 5));
		}
	}
}
