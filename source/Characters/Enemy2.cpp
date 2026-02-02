# include "Enemy2.hpp"
# include "Player.hpp"
# include "../Objects/Crate.hpp"

Enemy2::Enemy2(P2World& world, const Vec2& position) : EnemyBase(world, position)
{
	SizeF size{ 50, 75 };

	body = world.createRect(
		P2Dynamic,
		position,
		size,
		P2Material{
			.density = 0.0
		},
		P2Filter{
			.categoryBits = CollisionCategory::Enemy,
			.maskBits     = CollisionCategory::All & ~(CollisionCategory::Player | CollisionCategory::Crate | CollisionCategory::Enemy)
		}
	);

	body.addRectSensor(
		RectF{ -(size / 2), size },
		P2Filter{
			.categoryBits = CollisionCategory::Enemy,
			.maskBits     = CollisionCategory::Player | CollisionCategory::Crate | CollisionCategory::Enemy
		}
	);

	body.setFixedRotation(true);

	speed = Random(80, 100);
}

void Enemy2::update()
{
	EnemyBase::update();

	if (!damaged)
	{
		if (Abs(player_position.x - current_position.x) <= Scene::Width() / 2) body.setVelocity({ Sign(player_position.x - current_position.x) * speed, body.getVelocity().y });
	}
}

void Enemy2::draw() const
{
	if (body) TextureAsset(U"Enemy 2").resized({ 80, 80 }).rotated(body.getAngle()).drawAt(current_position, damaged ? ColorF{ 1.0, 0.25, 0.25, 0.5 } : ColorF{ 1.0 });

	EnemyBase::draw();
}

void Enemy2::onCollision(ObjectBase& object, const P2Collision&)
{
	if (dynamic_cast<Player*>(&object) || dynamic_cast<Crate*>(&object) || dynamic_cast<EnemyBase*>(&object)) object.getBody().applyLinearImpulse({ object.getBody().getPos().x < current_position.x ? -10 : 10, -10 });
}
