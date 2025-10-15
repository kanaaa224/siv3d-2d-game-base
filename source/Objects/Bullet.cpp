# include "Bullet.hpp"
# include "../Effects/TouchEffect.hpp"
# include "../Effects/SparkEffect.hpp"
# include "../Characters/Enemies/EnemyBase.hpp"
# include "../Utils/TimerUtils.hpp"

using namespace TimerUtils;

Bullet::Bullet(P2World& world, const Vec2& position, const Vec2& direction, float size) : ObjectBase(world, position)
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
			.maskBits     = CollisionCategory::All
		}
	);

	SetTimeout([this] { destroy(); }, 3000ms);

	body.applyLinearImpulse(direction.normalized() * 20);

	effect.add<TouchEffect>(position);
}

void Bullet::draw() const
{
	body.draw();

	effect.update();

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void Bullet::onHit(ObjectBase& object, const P2Collision& collision)
{
	if (object.getBody().getBodyType() == P2BodyType::Dynamic)
	{
		Vec2 diff = (object.getBody().getPos() - body.getPos()).normalized();

		object.getBody().applyLinearImpulse(diff * 500);

		effect.add<SparkEffect>(collision.contact(0).point);

		if (EnemyBase* enemy = dynamic_cast<EnemyBase*>(&object)) enemy->applyDamage(Random(50.0, 80.0));
	}

	body.release();
}
