# include "Base.hpp"
# include "../Player.hpp"

EnemyBase::EnemyBase(P2World& world, const Vec2& position) : CharacterBase(world, position), start_position(position)
{
	initialize();
}

void EnemyBase::initialize()
{
	max_hp = 100;

	hp = max_hp;
}

void EnemyBase::update()
{
	if (body.getPos().y >= (Scene::Height() + 100))
	{
		body.setPos(start_position);
		body.setVelocity({ 0, 0 });
	}
}

void EnemyBase::draw() const
{
	body.drawFrame();
}
