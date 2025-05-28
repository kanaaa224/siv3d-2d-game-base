# include "GameUI.hpp"

GameUI* GameUI::instance = nullptr;

GameUI::GameUI() : player_hp(0) {}

void GameUI::update() {}

void GameUI::draw() const
{
	Print << U"Player HP: " << player_hp;
}

GameUI* GameUI::GetInstance()
{
	if (instance == nullptr) instance = new GameUI();

	return instance;
}
