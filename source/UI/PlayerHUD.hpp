# pragma once

# include "../Common.hpp"

class PlayerHUD
{
public:
	static PlayerHUD* GetInstance();

	void update();
	void draw() const;

	void setPlayerHP(int32 hp, int32 max_hp) { player_hp = hp; player_max_hp = max_hp; }

private:
	PlayerHUD() : player_max_hp(0), player_hp(player_max_hp) {}

	int32 player_max_hp, player_hp;
};
