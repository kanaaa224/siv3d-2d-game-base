# include "1.hpp"
# include "../Objects/StageBackground.hpp"
# include "../Objects/Boxes/1.hpp"
# include "../Characters/Enemies/1.hpp"
# include "../Characters/Player.hpp"
# include "../UI/PlayerHUD.hpp"

Stage1::Stage1()
{
	initialize();
}

void Stage1::initialize()
{
	createObject<StageBackground>(Vec2{ 0, 0 });
	createObject<Box1>  (Vec2{ (Scene::Width() / 2) + 150, 500 });
	createObject<Enemy1>(Vec2{ (Scene::Width() / 2) - 150, 500 });
	createObject<Player>(Vec2{ (Scene::Width() / 2),       500 });

	floor = world.createRect(P2Static, Vec2{ 640, 600 }, SizeF{ 1000, 10 }, P2Material{ .friction = 0.9 });

	camera = Camera2D(Vec2{ (Scene::Width() / 2), (Scene::Height() / 2) }, 1.0, CameraControl::None_);
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

		int centerWidth  = (Scene::Width()  / 2);
		int centerHeight = (Scene::Height() / 2);

		if (centerWidth  > x) x = centerWidth;
		if (centerHeight < y) y = centerHeight;

		camera.setTargetCenter(Vec2{ x, y });
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
