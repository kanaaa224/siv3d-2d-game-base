# pragma once

# include "../Common.hpp"

class PlayerHUD
{
public:
	static PlayerHUD* GetInstance();

	void update();
	void draw() const;

	void setPlayerHP(float hp, float max_hp);

private:
	PlayerHUD() = default;

	float player_hp = 0.0f, player_max_hp = 0.0f;
};
