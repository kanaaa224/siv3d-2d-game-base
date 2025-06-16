# include "1.hpp"
# include "../Objects/StageBackground.hpp"
# include "../Objects/Boxes/1.hpp"
# include "../Objects/Boxes/2.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Characters/Enemies/1.hpp"
# include "../Characters/Enemies/2.hpp"
# include "../Characters/Player.hpp"
# include "../UI/PlayerHUD.hpp"
# include "../Utils/Timer.hpp"

using namespace TimerUtils;
using namespace std::chrono_literals;

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

	Player* player = nullptr;

	for (const auto& object : objects)
	{
		if ((player = dynamic_cast<Player*>(object))) break;
	}

	float player_hp     = 0;
	float player_max_hp = 0;

	static bool player_respawned = false;
	static bool player_spawn     = false;

	if (player)
	{
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

		player_respawned = false;
	}
	else
	{
		if (!player_respawned)
		{
			SetTimeout([this] { player_spawn = true; }, 1000ms);

			player_respawned = true;
		}

		if (player_spawn)
		{
			createObject<Player>(Scene::Center());

			player_spawn = false;
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
