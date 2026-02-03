# include "Blast.hpp"
# include "../Utils/TimerUtils.hpp"
# include "../Characters/CharacterBase.hpp"
# include "../Effects/Effect5.hpp"

using namespace TimerUtils;

Blast::Blast(P2World& world, const Vec2& position, const SizeF& size, bool player_apply_damage, const Milliseconds& life_time) : ObjectBase(world, position)
{
	body = world.createRect(
		P2Static,
		position,
		size,
		P2Material{
			.friction = 1.0
		},
		P2Filter{
			.categoryBits = CollisionCategory::Default,
			.maskBits     = CollisionCategory::Terrain
		}
	);

	body.addRectSensor(
		RectF{ -(size / 2), size },
		P2Filter{
			.categoryBits = CollisionCategory::Default,
			.maskBits     = CollisionCategory::Enemy | CollisionCategory::Crate
		}
	);

	if (player_apply_damage)
	{
		P2Filter filter = body.shape(1).getFilter();

		body.shape(1).setFilter({
			filter.categoryBits,
			static_cast<uint16>(filter.maskBits | CollisionCategory::Player)
		});
	}

	SetTimeout([this] { body.release(); }, life_time / 2);
	SetTimeout([this] { destroy();      }, life_time);

	effect.add<Effect5>(position);
}

void Blast::draw() const
{
	effect.update();

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void Blast::onCollision(ObjectBase& object, const P2Collision&)
{
	if (CharacterBase* character = dynamic_cast<CharacterBase*>(&object)) character->applyDamage(5);

	Vec2 direction = object.getBody().getPos() - body.getPos();

	double distance = direction.length();

	if (distance > 0.0)
	{
		direction /= distance;

		double impulsePower = 100.0;

		object.getBody().applyLinearImpulse(direction * impulsePower);
	}
}
