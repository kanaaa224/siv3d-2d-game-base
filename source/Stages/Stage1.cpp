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
	createObject<Box1>(Vec2{   (Scene::Width() / 2) + 150, 500 });
	createObject<Enemy1>(Vec2{ (Scene::Width() / 2) - 150, 500 });
	createObject<Player>(Vec2{ (Scene::Width() / 2),       500 });

	floor = world.createRect(P2Static, Vec2{ 640, 600 }, SizeF{ 1000, 10 }, P2Material{ .friction = 0.9 });

	camera = Camera2D(Vec2{ (Scene::Width() / 2), (Scene::Height() / 2) }, 1.0, CameraControl::None_);
}

void Stage1::update()
{
	Stage::update();

	static Stopwatch respawnTimer{ StartImmediately::No };

	float player_hp = 0;

	Player* player = nullptr;

	for (const auto& object : objects)
	{
		if ((player = dynamic_cast<Player*>(object))) break;
	}

	if (player)
	{
		respawnTimer.reset();

		player_hp = player->getHP();

		double y = player->getBody().getPos().y;

		int centerHeight = (Scene::Height() / 2);

		if (centerHeight < y) y = centerHeight;

		camera.setTargetCenter(Vec2{ player->getBody().getPos().x, y });
	}
	else
	{
		if (!respawnTimer.isRunning()) respawnTimer.restart();

		if (respawnTimer.sF() >= 1.0)
		{
			createObject<Player>(Vec2{ (Scene::Width() / 2), 500 });

			respawnTimer.reset();
		}
	}

	camera.update();

	GameUI* gameUI = GameUI::GetInstance();

	gameUI->setPlayerHP(player_hp);
	gameUI->update();
}

void Stage1::draw() const
{
	ClearPrint();

	const auto t = camera.createTransformer();

	Stage::draw();

	floor.draw();

	Print << U"Objects: " << objects.size();

	GameUI::GetInstance()->draw();
}

void Stage1::NewInstance()
{
	if (instance != nullptr) delete instance;

	instance = new Stage1();
}
