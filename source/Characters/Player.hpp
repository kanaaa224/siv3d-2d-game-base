# pragma once

# include "CharacterBase.hpp"

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
