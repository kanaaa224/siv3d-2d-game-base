# include "Game.hpp"
# include "../Stages/Stage.hpp"
# include "../Stages/Stage1.hpp"

Game::Game(const InitData& init) : IScene{ init }
{

}

void Game::update()
{
	Stage* stage = Stage1::GetInstance();

	stage->update();

	if (MouseL.down()) changeScene(SceneState::Title, 0.5s);
}

void Game::draw() const
{
	Stage* stage = Stage1::GetInstance();

	stage->draw();
}
