# include "Scaffold.hpp"
# include "../Characters/Player.hpp"

Scaffold::Scaffold(P2World& world, const Vec2& position, const SizeF& size, bool passThrough) : ObjectBase(world, position), pass_through(passThrough)
{
	body = world.createRect(
		P2Static,
		position,
		size,
		P2Material{
			.friction = 0.9
		},
		P2Filter{
			.categoryBits = CollisionCategory::Scaffold,
			.maskBits     = CollisionCategory::All
		}
	);

	body.addRectSensor(
		RectF{ -(size / 2) - Vec2{ 10, 10 }, size + Vec2{ 20, 20 } },
		P2Filter{
			.categoryBits = CollisionCategory::Scaffold,
			.maskBits     = CollisionCategory::Player
		}
	);
}

void Scaffold::draw() const
{
	body.shape(0).draw(pass_through ? Palette::White.withAlpha(128) : Palette::White);

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void Scaffold::onHit(ObjectBase& object, const P2Collision&)
{
	if (Player* player = dynamic_cast<Player*>(&object))
	{
		if (object.getBody().getPos().y > body.getPos().y && pass_through) player->descendScaffold();
	}
}
