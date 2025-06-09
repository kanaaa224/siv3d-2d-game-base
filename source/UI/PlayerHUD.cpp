# include "PlayerHUD.hpp"

PlayerHUD* PlayerHUD::instance = nullptr;

PlayerHUD::PlayerHUD() : player_hp(0.0f), player_max_hp(0.0f) {}

void PlayerHUD::update() {}

void PlayerHUD::draw() const
{
	Print << U"Player HP: " << player_hp << U" / " << player_max_hp;
}

PlayerHUD* PlayerHUD::GetInstance()
{
	if (instance == nullptr) instance = new PlayerHUD();

	return instance;
}
