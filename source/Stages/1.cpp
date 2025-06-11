# include "1.hpp"
# include "../Objects/StageBackground.hpp"
# include "../Objects/Boxes/1.hpp"
# include "../Objects/Boxes/2.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Characters/Enemies/1.hpp"
# include "../Characters/Enemies/2.hpp"
# include "../Characters/Player.hpp"
# include "../UI/PlayerHUD.hpp"

Stage1::Stage1()
{
	initialize();
}

void Stage1::initialize()
{
	createObject<StageBackground>();

	createObject<Box1>    (Scene::Center() + Vec2{  150,    0 });
	createObject<Box2>    (Scene::Center() + Vec2{  150, -100 });
	createObject<Punipuni>(Scene::Center() + Vec2{    0, -200 });
	createObject<Enemy1>  (Scene::Center() + Vec2{ -150,    0 });
	createObject<Enemy2>  (Scene::Center() + Vec2{ -260,    0 });
	createObject<Player>  (Scene::Center());

	floor = world.createRect(P2Static, { Scene::Center().x, (Scene::Height() - 100) }, SizeF{ (Scene::Width() - 100), 10 }, P2Material{ .friction = 0.9 });

	camera = Camera2D(Scene::Center(), 1.0, CameraControl::None_);
}

void Stage1::update()
{
	Stage::update();

	static Stopwatch respawnTimer{ StartImmediately::No };

	float player_hp     = 0;
	float player_max_hp = 0;

	Player* player = nullptr;

	for (const auto& object : objects)
	{
		if ((player = dynamic_cast<Player*>(object))) break;
	}

	if (player)
	{
		respawnTimer.reset();

		player_hp     = player->getHP();
		player_max_hp = player->getMaxHP();

		double x = player->getBody().getPos().x;
		double y = player->getBody().getPos().y;

		const Point center = Scene::Center();

		if (center.x > x) x = center.x;
		if (center.y < y) y = center.y;

		camera.setTargetCenter({ x, y });
		
		for (const auto& object : objects)
		{
			if (StageBackground* stageBackground = dynamic_cast<StageBackground*>(object))
			{
				stageBackground->setCameraPosition(camera.getTargetCenter() - Scene::Center());
			}
		}
	}
	else
	{
		if (!respawnTimer.isRunning()) respawnTimer.restart();

		if (respawnTimer.sF() >= 1.0)
		{
			createObject<Player>(Scene::Center());

			respawnTimer.reset();
		}
	}

	camera.update();

	PlayerHUD* playerHUD = PlayerHUD::GetInstance();

	playerHUD->setPlayerHP(player_hp, player_max_hp);
	playerHUD->update();
}

void Stage1::draw() const
{
	ClearPrint();

	Print << U"オブジェクト数: " << objects.size();

	{
		const auto t = camera.createTransformer();

		Stage::draw();

		floor.draw();
	}

	PlayerHUD::GetInstance()->draw();
}

void Stage1::NewInstance()
{
	if (instance != nullptr) delete instance;

	instance = new Stage1();
}
