# pragma once

# include "CharacterBase.hpp"

# define PLAYER_MOVE_POWER 275
# define PLAYER_JUMP_POWER 500
# define PLAYER_MAX_JUMP_HOLD 100ms

class Player : public CharacterBase
{
public:
	Player(P2World& world, const Vec2& position = { 0, 0 });

	void update() override;
	void draw() const override;

	virtual void onHit(ObjectBase& object, const P2Collision& collision) override;
	void onDamaged(int32 amount) override;

	void setCamera(const Camera2D* camera) { stage_camera = camera; }

	void passThrough(uint16 category = CollisionCategory::None) { if (pass_through_category != CollisionCategory::None) return; pass_through_area = RectF{ 0 }; pass_through_category = category; }

	void descendScaffold() { if (pass_through_category != CollisionCategory::None) return; descend_scaffold = true; passThrough(CollisionCategory::Scaffold); }

private:
	Vec2 current_position;
	Vec2 start_position;
	Vec2 aim;

	P2Filter filter;

	RectF pass_through_area;

	uint16 pass_through_category;

	const Camera2D* stage_camera = nullptr;

	bool damaged;
	bool descend_scaffold;
	bool shooted;

	mutable bool mirrored;

	void handleInput();
	void moveLeft();
	void moveRight();
	void jump(Duration duration = 1ms);
	void shoot();
};
