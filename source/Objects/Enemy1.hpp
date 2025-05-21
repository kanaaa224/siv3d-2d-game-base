# pragma once

# include "CharacterBase.hpp"

class Enemy1 : public CharacterBase
{
public:
	Enemy1(P2World& world, const Vec2& position);
	~Enemy1();

	void update() override;
	void draw() const override;

private:
	void initialize();
	void finalize();
};
