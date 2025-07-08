# pragma once

# include "CharacterBase.hpp"

# define PLAYER_MAX_HP 100

class Player : public CharacterBase
{
public:
	Player(P2World& world, const Vec2& position = { 0, 0 });
	~Player() = default;

	void update() override;
	void draw() const override;

private:
	void initialize();
};
