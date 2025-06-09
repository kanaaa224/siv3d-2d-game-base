# pragma once

# include "../Common.hpp"

class PlayerHUD
{
public:
	PlayerHUD();
	~PlayerHUD() = default;

	void update();
	void draw() const;

	void setPlayerHP(float hp = 0.0f, float max_hp = 0.0f) { player_hp = hp; player_max_hp = max_hp; }

	static PlayerHUD* GetInstance();

private:
	float player_hp, player_max_hp;

	static PlayerHUD* instance;
};
