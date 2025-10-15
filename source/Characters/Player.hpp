# pragma once

# include "CharacterBase.hpp"

# define PLAYER_MAX_HP 100
# define PLAYER_MOVE_POWER 275
# define PLAYER_JUMP_POWER 625
# define PLAYER_MAX_JUMP_HOLD 150ms
# define PLAYER_MIN_JUMP_HOLD 100ms

class Player : public CharacterBase
{
public:
	Player(P2World& world, const Vec2& position = { 0, 0 });

	void update() override;
	void draw() const override;

	virtual void onHit(ObjectBase& object, const P2Collision& collision) override;
	void onDamaged(float amount) override;

	void setCamera(const Camera2D* camera) { stage_camera = camera; }

private:
	Vec2 current_position;
	Vec2 start_position;

	const Camera2D* stage_camera = nullptr;

	bool damaged;

	Effect effect;

	Vec2 aim;

	void initialize();
	void handleInput();
	void moveLeft();
	void moveRight();
	void jump(double power = 1.0);
	void descendScaffold();
	void shoot();
};
