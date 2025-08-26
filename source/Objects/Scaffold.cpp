# include "Scaffold.hpp"
# include "../Characters/Player.hpp"
# include "../Utils/TimerUtils.hpp"

using namespace TimerUtils;
using namespace std::chrono_literals;

Scaffold::Scaffold(P2World& world, const Vec2& position) : ObjectBase(world, position)
{
	SizeF size{ Random(100, 500), 10 };

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
		RectF{ -(size / 2) - Vec2{ 0, 10 }, size + Vec2{ 0, 20 } },
		P2Filter{
			.categoryBits = CollisionCategory::Scaffold,
			.maskBits     = CollisionCategory::Player
		}
	);
}

void Scaffold::draw() const
{
	body.shape(0).draw(Palette::White);

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void Scaffold::onHit(ObjectBase& object, const P2Collision&)
{
	if (Player* player = dynamic_cast<Player*>(&object))
	{
		if (object.getBody().getPos().y < body.getPos().y) return;

		P2Filter filter = player->getBody().shape(0).getFilter();

		if (!(filter.maskBits & CollisionCategory::Scaffold)) return;

		player->getBody().shape(0).setFilter({
			filter.categoryBits,
			static_cast<uint16>(filter.maskBits & ~CollisionCategory::Scaffold)
		});

		SetTimeout([this, player, filter] { player->getBody().shape(0).setFilter(filter); }, 500ms);
	}
}
