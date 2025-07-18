# include "Game.hpp"
# include "../Stages/Stage1.hpp"
# include "../Utils/TimerUtils.hpp"

Game::Game(const InitData& init) : IScene{ init }
{
	TimerUtils::ClearTasks();

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
	static bool pause = false;

	if (KeyP.down()) pause = !pause;

	if (pause) return;

	Stage::GetInstance()->update();

	TimerUtils::Update();
}

void Game::draw() const
{
	Stage::GetInstance()->draw();
}
