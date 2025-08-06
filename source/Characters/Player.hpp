# pragma once

# include "CharacterBase.hpp"

# define PLAYER_MAX_HP 100
# define PLAYER_MOVE_POWER 250
# define PLAYER_JUMP_POWER 600

class Player : public CharacterBase
{
public:
	Player(P2World& world, const Vec2& position = { 0, 0 });

	void update() override;
	void draw() const override;

private:
	void initialize();
	void handleInput();
	void moveLeft();
	void moveRight();
	void jump();
};
