# pragma once

# include "CharacterBase.hpp"

class Player : public CharacterBase
{
public:
	Player(P2World& world, const Vec2& position);
	~Player() = default;

	void update() override;
	void draw() const override;

private:
	bool mirrored;

	void initialize();
};
