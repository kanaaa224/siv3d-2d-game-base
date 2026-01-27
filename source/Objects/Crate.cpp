# include "Crate.hpp"

Crate::Crate(P2World& world, const Vec2& position, bool playerPassThrough) : ObjectBase(world, position)
{
	SizeF size{ 50, 50 };

	body = world.createRect(
		P2Dynamic,
		position,
		size,
		P2Material{},
		P2Filter{
			.categoryBits = CollisionCategory::Crate,
			.maskBits     = CollisionCategory::All
		}
	);

	if (playerPassThrough)
	{
		P2Filter filter = body.shape(0).getFilter();

		body.shape(0).setFilter({
			filter.categoryBits,
			static_cast<uint16>(filter.maskBits & ~CollisionCategory::Player)
		});
	}
}

void Crate::update()
{
	if (body.getPos().y >= (Scene::Height() + 100)) deleteSelf();
}

void Crate::draw() const
{
	TextureAsset(U"Crate").resized({ 55, 55 }).rotated(body.getAngle()).drawAt(body.getPos());

#ifdef _DEBUG
	body.drawFrame();
#endif
}
