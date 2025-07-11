# include "Enemy1.hpp"
# include "../Player.hpp"
# include "../../Effects/SparkEffect.hpp"
# include "../../Effects/ScoreEffect.hpp"
# include "../../Effects/TouchEffect.hpp"
# include "../../Effects/BubbleEffect.hpp"

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

void Enemy1::draw() const
{
	TextureAsset(U"Enemy 1").resized({ 105, 105 }).rotated(body.getAngle()).drawAt(body.getPos());

	EnemyBase::draw();

	effect.update();
}

void Enemy1::onHit(ObjectBase& object, const P2Collision& collision)
{
	if (Player* player = dynamic_cast<Player*>(&object))
	{
		if (object.getBody().getPos().y < (body.getPos().y - 100))
		{
			object.getBody().applyLinearImpulse({ 0, -200 });

			int damage = Random(5, 25);

			this->applyDamage((float)damage);

			static Font font{ FontMethod::MSDF, 48, Typeface::Heavy, FontStyle::Italic };

			effect.add<ScoreEffect>(collision.contact(0).point, damage, font);
			effect.add<SparkEffect>(collision.contact(0).point);
		}
		else
		{
			if (object.getBody().getPos().x < body.getPos().x)
			{
				object.getBody().applyLinearImpulse({ -100, -100 });

				effect.add<TouchEffect>(collision.contact(0).point);
			}
			else
			{
				object.getBody().applyLinearImpulse({ 100, -100 });

				effect.add<BubbleEffect>(collision.contact(0).point, Random(0.0, 360.0));
			}

			player->applyDamage(10);
		}
	}
}
