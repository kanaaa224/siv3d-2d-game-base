# include "Game.hpp"
# include "../Stages/Stage1.hpp"

Game::Game(const InitData& init) : IScene{ init }
{
	switch (getData().current_stage)
	{
	case 0:
		Stage::NewInstance();
		break;

	case 1:
		Stage1::NewInstance();
		break;

	default:
		break;
	}
	
	Stage::GetInstance()->setSceneFunctions(
		[this](SceneState s, Duration d) { changeScene(s, d); },
		[this]() -> SceneData& { return getData(); }
	);
}

Game::~Game()
{
	Stage::DeleteInstance();
}

void Game::update()
{
	Stage::GetInstance()->update();
}

void Game::draw() const
{
	Stage::GetInstance()->draw();
}
