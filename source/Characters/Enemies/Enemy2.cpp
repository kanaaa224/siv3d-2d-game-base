# include "Enemy2.hpp"
# include "../Player.hpp"
# include "../../Objects/Boxes/Box1.hpp"
# include "../../Objects/Boxes/Box2.hpp"

Enemy2::Enemy2(P2World& world, const Vec2& position) : EnemyBase(world, position)
{
	SizeF size{ 75, 100 };

	body = world.createRect(
		P2Dynamic,
		position,
		size,
		P2Material{
			.density = 0.0
		},
		P2Filter{
			.categoryBits = CollisionCategory::Enemy,
			.maskBits     = CollisionCategory::All & ~(CollisionCategory::Player | CollisionCategory::Box)
		}
	);

	body.addRectSensor(
		RectF{ -(size / 2), size },
		P2Filter{
			.categoryBits = CollisionCategory::Enemy,
			.maskBits     = CollisionCategory::Player | CollisionCategory::Box
		}
	);

	body.setFixedRotation(true);
}

void Enemy2::update()
{
	EnemyBase::update();

	if (Abs(player_position.x - body.getPos().x) <= Scene::Width() / 2) body.setVelocity({ Sign(player_position.x - current_position.x) * 90, body.getVelocity().y });
}

void Enemy2::draw() const
{
	TextureAsset(U"Enemy 2").resized({ 105, 105 }).rotated(body.getAngle()).drawAt(body.getPos(), damaged ? ColorF{ 1.0, 0.25, 0.25, 0.5 } : ColorF{ 1.0 });

	EnemyBase::draw();
}

void Enemy2::onHit(ObjectBase& object, const P2Collision&)
{
	if (dynamic_cast<Player*>(&object) || dynamic_cast<Box1*>(&object) || dynamic_cast<Box2*>(&object)) object.getBody().applyLinearImpulse({ object.getBody().getPos().x < body.getPos().x ? -10 : 10, -10 });
}
