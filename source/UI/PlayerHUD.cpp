# include "PlayerHUD.hpp"

PlayerHUD* PlayerHUD::GetInstance()
{
	static PlayerHUD instance;

	return &instance;
}

void PlayerHUD::update() {}

void PlayerHUD::draw() const
{
	Print << U"Player HP: " << player_hp << U" / " << player_max_hp;
}

void PlayerHUD::setPlayerHP(float hp, float max_hp)
{
	player_hp     = hp;
	player_max_hp = max_hp;
}
