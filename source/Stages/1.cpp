# include "1.hpp"
# include "../Objects/StageBackground.hpp"
# include "../Objects/Boxes/1.hpp"
# include "../Objects/Boxes/2.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Characters/Enemies/1.hpp"
# include "../Characters/Player.hpp"
# include "../UI/PlayerHUD.hpp"

Stage1::Stage1()
{
	initialize();
}

void Stage1::initialize()
{
	const int width  = Scene::Width();
	const int height = Scene::Height();
	
	const int halfWidth  = (width  / 2);
	const int halfHeight = (height / 2);

	createObject<StageBackground>(Vec2{ 0, 0 });

	createObject<Box1>    (Vec2{ halfWidth + 150, halfHeight       });
	createObject<Box2>    (Vec2{ halfWidth + 150, halfHeight - 100 });
	createObject<Punipuni>(Vec2{ halfWidth,       halfHeight - 200 });
	createObject<Enemy1>  (Vec2{ halfWidth - 150, halfHeight       });
	createObject<Player>  (Vec2{ halfWidth,       halfHeight       });

	floor = world.createRect(P2Static, Vec2{ halfWidth, (height - 100) }, SizeF{ (width - 100), 10 }, P2Material{ .friction = 0.9 });

	camera = Camera2D(Vec2{ halfWidth, halfHeight }, 1.0, CameraControl::None_);
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

		const int halfWidth  = (Scene::Width()  / 2);
		const int halfHeight = (Scene::Height() / 2);

		if (halfWidth  > x) x = halfWidth;
		if (halfHeight < y) y = halfHeight;

		camera.setTargetCenter(Vec2{ x, y });
		
		for (const auto& object : objects)
		{
			if (StageBackground* stagebackground = dynamic_cast<StageBackground*>(object))
			{
				stagebackground->setCameraPosition(camera.getTargetCenter() - Scene::Center());
			}
		}
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
