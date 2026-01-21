# include "Stage1.hpp"
# include "../Objects/StageBackground.hpp"
# include "../Objects/Boxes/Box1.hpp"
# include "../Objects/Boxes/Box2.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Objects/Scaffold.hpp"
# include "../Objects/Ground.hpp"
# include "../Characters/Enemies/Enemy1.hpp"
# include "../Characters/Enemies/Enemy2.hpp"
# include "../Characters/Player.hpp"
# include "../UI/PlayerHUD.hpp"
# include "../Utils/TimerUtils.hpp"

using namespace TimerUtils;

Stage1::Stage1()
{
	initialize();
}

void Stage1::initialize()
{
	createObject<StageBackground>();

	createObject<Punipuni>(Scene::Center() + Vec2{ 0, -200 });

	createObject<Player>(Scene::Center());

	createObject<Ground>(Vec2{ Scene::Center().x, (Scene::Height() - 100) }, SizeF{ (Scene::Width() - 100), 10 });

	camera = Camera2D(Scene::Center(), 1.0, CameraControl::None_);

	SetInterval([this] { createObject<Box1>(Scene::Center() + Vec2{ 150, -100 }); }, 2s);
	SetInterval([this] { createObject<Box2>(Scene::Center() + Vec2{ 225, -100 }); }, 2s);

	SetInterval([this] { createObject<Enemy1>(Scene::Center() + Vec2{ -200, -200 }); }, 7s);
	SetInterval([this] { createObject<Enemy2>(Scene::Center() + Vec2{ -375, -200 }); }, 5s);

	for (int i = 1; i <= 50; i++) createObject<Scaffold>(Vec2{ Scene::Width() + i * 250, Scene::Center().y - (i % 2 ? 0 : 250) }, SizeF{ Random(200, 500), 10 }, Random(1));

	for (int i = 1; i <= 50; i++) createObject<Enemy1>(Vec2{ Scene::Width() + i * 250, (Scene::Center().y - (i % 2 ? 0 : 250)) - 100 });
	for (int i = 1; i <= 50; i++) createObject<Enemy2>(Vec2{ Scene::Width() + i * 250, (Scene::Center().y - (i % 2 ? 0 : 250)) - 100 });
}

void Stage1::update()
{
	Stage::update();

	Player* player = nullptr;

	for (const auto& object : objects) if ((player = dynamic_cast<Player*>(object))) break;

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

		player->setCamera(&camera);

		for (const auto& object : objects)
		{
			if (StageBackground* stageBackground = dynamic_cast<StageBackground*>(object))
			{
				stageBackground->setCameraPosition(camera.getTargetCenter() - Scene::Center());
			}

			if (EnemyBase* enemy = dynamic_cast<EnemyBase*>(object))
			{
				enemy->setPlayerPosition(player->getBody().getPos());
			}
		}

		player_respawned = false;
	}
	else
	{
		if (!player_respawned)
		{
			SetTimeout([this] { player_spawn = true; }, 1s);

			player_respawned = true;
		}

		if (player_spawn)
		{
			createObject<Player>(Scene::Center());

			player_spawn = false;
		}
	}

	camera.update();

	PlayerHUD::GetInstance()->setPlayerHP(player_hp, player_max_hp);
}

void Stage1::draw() const
{
	Print << U"オブジェクト数: " << objects.size();

	Print << U"タイマーイベント数: " << GetTasks().size();

	{
		const auto t2d = camera.createTransformer();

		Stage::draw();
	}
}

void Stage1::NewInstance()
{
	DeleteInstance();

	instance = new Stage1();
}
