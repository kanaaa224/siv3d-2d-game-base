# include "Stage1.hpp"

# include "../Objects/GameUI.hpp"
# include "../Objects/StageBackground.hpp"
# include "../Objects/Box1.hpp"
# include "../Objects/Enemy1.hpp"
# include "../Objects/Player.hpp"

Stage1::Stage1()
{
	this->initialize();
}

void Stage1::initialize()
{
	createObject<StageBackground>(Vec2{ 0, 0 });
	createObject<Box1>(Vec2{ 640, 500 });
	createObject<Enemy1>(Vec2{ 520, 500 });
	createObject<Player>(Vec2{ 320, 500 });

	floor = world.createRect(P2Static, Vec2{ 640, 600 }, SizeF{ 1000, 10 });
}

void Stage1::update()
{
	__super::update();

	GameUI* gameUI = GameUI::GetInstance();

	gameUI->update();
}

void Stage1::draw() const
{
	ClearPrint();

	__super::draw();

	floor.draw();

	Print << U"Objects: " << objects.size();

	GameUI* gameUI = GameUI::GetInstance();

	gameUI->draw();
}

void Stage1::NewInstance()
{
	if (instance != nullptr) delete instance;

	instance = new Stage1();
}
