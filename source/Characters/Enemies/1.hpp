# pragma once

# include "Base.hpp"

class Enemy1 : public EnemyBase
{
public:
	Enemy1(P2World& world, const Vec2& position);
	~Enemy1() = default;
};
