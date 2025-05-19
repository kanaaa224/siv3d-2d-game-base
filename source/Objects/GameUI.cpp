# include "GameUI.hpp"

GameUI* GameUI::instance = nullptr;

GameUI::GameUI()
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

}

void GameUI::finalize()
{

}

GameUI* GameUI::GetInstance()
{
	if (instance == nullptr) instance = new GameUI();

	return instance;
}
