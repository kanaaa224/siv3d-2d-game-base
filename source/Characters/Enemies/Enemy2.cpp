# include "Enemy2.hpp"
# include "../Player.hpp"

Enemy2::Enemy2(P2World& world, const Vec2& position) : EnemyBase(world, position)
{
	SizeF size { 75, 100 };

	body = world.createRect(
		P2Dynamic,
		position,
		size,
		P2Material { .density = 0.0 },
		P2Filter {
			.categoryBits = CollisionCategory::Enemy,
			.maskBits     = CollisionCategory::All & ~CollisionCategory::Player
		}
	);

	body.addRectSensor(RectF{ -(size / 2), size }, P2Filter{ .categoryBits = CollisionCategory::Enemy, .maskBits = CollisionCategory::Player });

	body.setFixedRotation(true);
}

void Enemy2::draw() const
{
	TextureAsset(U"Enemy 2").resized({ 105, 105 }).rotated(body.getAngle()).drawAt(body.getPos());

	EnemyBase::draw();
}

void Enemy2::onHit(ObjectBase& object, const P2Collision&)
{
	if (Player* player = dynamic_cast<Player*>(&object))
	{
		if (object.getBody().getPos().x < body.getPos().x)
		{
			object.getBody().applyLinearImpulse({ -10, -10 });
		}
		else
		{
			object.getBody().applyLinearImpulse({ 10, -10 });
		}
	}
}
