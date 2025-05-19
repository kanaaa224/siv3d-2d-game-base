# pragma once

# include "CharacterBase.hpp"

class Player : public CharacterBase
{
public:
	Player(P2World& world, const Vec2& position);
	~Player();

	void update() override;
	void draw() const override;

private:
	void initialize();
	void finalize();
};
