# include "Bullet.hpp"
# include "../Effects/TouchEffect.hpp"
# include "../Effects/SparkEffect.hpp"
# include "../Characters/EnemyBase.hpp"
# include "../Utils/TimerUtils.hpp"

using namespace TimerUtils;

Bullet::Bullet(P2World& world, const Vec2& position, const Vec2& direction, double size) : ObjectBase(world, position), hit(false)
{
	body = world.createCircle(
		P2Dynamic,
		position,
		size,
		P2Material{
			.friction = 0.9
		},
		P2Filter{
			.categoryBits = CollisionCategory::Bullet,
			.maskBits     = CollisionCategory::All & ~CollisionCategory::Enemy
		}
	);

	body.addCircleSensor(
		Circle{ size },
		P2Filter{
			.categoryBits = CollisionCategory::Bullet,
			.maskBits     = CollisionCategory::Enemy
		}
	);

	SetTimeout([this] { destroy(); }, 3000ms);

	body.applyLinearImpulse(direction.normalized() * 20);

	effect.add<TouchEffect>(position);
}

void Bullet::update()
{
	if (body) current_position = body.getPos();
}

void Bullet::draw() const
{
	body.draw();

	effect.update();

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void Bullet::onCollision(ObjectBase& object, const P2Collision&)
{
	if (object.getBody().getBodyType() == P2BodyType::Dynamic)
	{
		object.getBody().setVelocity(-object.getBody().getVelocity());

		if (EnemyBase* enemy = dynamic_cast<EnemyBase*>(&object)) enemy->applyDamage(Random(20, 40));
	}

	if (object.getBody().getBodyType() == P2BodyType::Static) body.release();

	if (!hit) effect.add<SparkEffect>(current_position);

	hit = true;
}
