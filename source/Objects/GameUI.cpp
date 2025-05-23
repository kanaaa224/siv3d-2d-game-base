# include "GameUI.hpp"

GameUI* GameUI::instance = nullptr;

GameUI::GameUI() : player_hp(0)
{
	this->initialize();
}

GameUI::~GameUI()
{
	this->finalize();
}

void GameUI::initialize()
{

}

void GameUI::update()
{

}

void GameUI::draw() const
{
	Print << U"Player HP: " << player_hp;
}

void GameUI::finalize()
{

}

GameUI* GameUI::GetInstance()
{
	if (instance == nullptr) instance = new GameUI();

	return instance;
}
