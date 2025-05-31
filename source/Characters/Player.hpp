# pragma once

# include "Base.hpp"

class Player : public CharacterBase
{
public:
	Player(P2World& world, const Vec2& position);
	~Player() = default;

	void update() override;
	void draw() const override;

private:
	void initialize();
};
