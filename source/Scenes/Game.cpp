# include "Game.hpp"
# include "../Stages/Stage1.hpp"
# include "../Utils/TimerUtils.hpp"
# include "../UI/PlayerHUD.hpp"

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
		[this](SceneState s, Duration d) { return changeScene(s, d); },
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

	if (KeyP.down()) pause = not pause;

	if (pause) return;

	Stage    ::GetInstance()->update();
	PlayerHUD::GetInstance()->update();

	TimerUtils::Update();
}

void Game::draw() const
{
	ClearPrint();

	Stage    ::GetInstance()->draw();
	PlayerHUD::GetInstance()->draw();
}
