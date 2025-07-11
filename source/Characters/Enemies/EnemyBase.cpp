# include "EnemyBase.hpp"
# include "../Player.hpp"

EnemyBase::EnemyBase(P2World& world, const Vec2& position) : CharacterBase(world, position), start_position(position)
{
	initialize();
}

void EnemyBase::initialize()
{
	hp = max_hp = ENEMY_MAX_HP;
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
#ifdef _DEBUG
	body.drawFrame();
#endif
}
