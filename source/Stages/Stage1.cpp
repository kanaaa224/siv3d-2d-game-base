# include "Stage1.hpp"
# include "../Objects/StageBackground.hpp"
# include "../Objects/Crate.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Objects/Scaffold.hpp"
# include "../Objects/Ground.hpp"
# include "../Objects/Wall.hpp"
# include "../Characters/Enemy1.hpp"
# include "../Characters/Enemy2.hpp"
# include "../UI/PlayerHUD.hpp"
# include "../Utils/TimerUtils.hpp"

using namespace TimerUtils;

Stage1::Stage1() : player(nullptr)
{
	camera = Camera2D(Scene::Center(), 1.0, CameraControl::None_);

	createObject<StageBackground>();

	generated_position = Vec2{ 10, Scene::Size().y - 10 };
}

void Stage1::generate(int32 template_index = 0)
{
	int32 terrain_thickness = 10;
	int32 passage_width     = 300;

	int32 level = sceneData().level;

	SizeF size{};

	switch (template_index)
	{
	case 0: size = { 1260,  700 }; break;
	case 1: size = { 2500, 1500 }; break;
	case 2: size = { 3000, 1000 }; break;
	case 3: size = { 3500, 1500 }; break;
	default: return;
	}

	RectF room{ generated_position - Vec2{ 0, size.y }, size };

	switch (template_index)
	{
	case 0:
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 200) createObject<Enemy1>(room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }); }, Max(500ms, 3s - (500ms * level)));
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 200) createObject<Enemy2>(room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }); }, Max(900ms, 7s - (500ms * level)));

		createObject<Scaffold>(room.center() + Vec2{  -50,  150 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -300,  -50 }, SizeF{ 300, 10 });
		createObject<Scaffold>(room.center() + Vec2{  500, -150 }, SizeF{ 100, 10 });
		createObject<Scaffold>(room.center() + Vec2{  450,   75 }, SizeF{ 200, 10 });
		break;

	case 1:
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 200) createObject<Enemy1>(room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }); }, Max(200ms, 1s - (200ms * level)));
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 300) createObject<Enemy2>(room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }); }, Max(400ms, 2s - (200ms * level)));
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 200) createObject<Crate> (room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }); }, Max(500ms, 3s - (300ms * level)));
			
		createObject<Scaffold>(room.center() + Vec2{  -900,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -300,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   300,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   900,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -600,  400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{     0,  400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   600,  400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -900,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -300,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   300,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   900,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -600,    0 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{     0,    0 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   600,    0 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -900, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -300, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   300, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   900, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -600, -400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{     0, -400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   600, -400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -900, -600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -300, -600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   300, -600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   900, -600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1100,  400 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1100,  400 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1100, -400 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1100, -400 }, SizeF{ 200, 10 });
		break;

	case 2:
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 200) createObject<Enemy1>  (room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }); }, Max(200ms, 1s - (200ms * level)));
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 200) createObject<Punipuni>(room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }); }, 15s);
			
		createObject<Scaffold>(room.center() + Vec2{ -1300,  300 }, SizeF{ 300, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -900,  100 }, SizeF{ 300, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -500, -100 }, SizeF{ 300, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -100, -300 }, SizeF{ 300, 10 });
		createObject<Scaffold>(room.center() + Vec2{   300, -100 }, SizeF{ 300, 10 });
		createObject<Scaffold>(room.center() + Vec2{   700,  100 }, SizeF{ 300, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1100,  300 }, SizeF{ 300, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1100, -200 }, SizeF{ 250, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -700,  350 }, SizeF{ 250, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -300,  150 }, SizeF{ 250, 10 });
		createObject<Scaffold>(room.center() + Vec2{   100,  350 }, SizeF{ 250, 10 });
		createObject<Scaffold>(room.center() + Vec2{   500,  150 }, SizeF{ 250, 10 });
		createObject<Scaffold>(room.center() + Vec2{   900, -250 }, SizeF{ 250, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1300, -100 }, SizeF{ 250, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1400,  -50 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1000, -350 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -600, -250 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -200,    0 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{   200, -350 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{   600, -300 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1000,    0 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1400,  200 }, SizeF{ 200, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1200,  150 }, SizeF{ 150, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -800, -150 }, SizeF{ 150, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -400,  300 }, SizeF{ 150, 10 });
		createObject<Scaffold>(room.center() + Vec2{     0, -150 }, SizeF{ 150, 10 });
		createObject<Scaffold>(room.center() + Vec2{   400,  300 }, SizeF{ 150, 10 });
		createObject<Scaffold>(room.center() + Vec2{   800, -100 }, SizeF{ 150, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1200, -350 }, SizeF{ 150, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -150,  300 }, SizeF{ 150, 10 });
		createObject<Scaffold>(room.center() + Vec2{   150,  300 }, SizeF{ 150, 10 });
		break;

	case 3:
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 200) createObject<Enemy1>(room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }      ); }, Max(200ms, 1s - (200ms * level)));
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 300) createObject<Enemy2>(room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }      ); }, Max(400ms, 2s - (200ms * level)));
		SetInterval([this, room] { if (player && room.intersects(player->getBody().getPos()) && objects.size() <= 200) createObject<Crate> (room.center() + Vec2{ Random(-500, 500), Random(-150, 150) }, true); }, Max(500ms, 3s - (300ms * level)));
			
		createObject<Scaffold>(room.center() + Vec2{ -1500,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -900,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -300,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   300,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   900,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1500,  600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1200,  400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -600,  400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{     0,  400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   600,  400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1200,  400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1500,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -900,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -300,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   300,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   900,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1500,  200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1200,    0 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -600,    0 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{     0,    0 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   600,    0 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1200,    0 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1500, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -900, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -300, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   300, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   900, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1500, -200 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1200, -400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  -600, -400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{     0, -400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{   600, -400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1200, -400 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{ -1500, -600 }, SizeF{ 400, 10 });
		createObject<Scaffold>(room.center() + Vec2{  1500, -600 }, SizeF{ 400, 10 });
		break;

	default:
		break;
	}

	createObject<Wall>(
		room.leftCenter() - Vec2{ (terrain_thickness / 2), 0 },
		SizeF{ terrain_thickness, room.left().length() }
	);

	createObject<Wall>(
		room.rightCenter() + Vec2{ (terrain_thickness / 2), 0 },
		SizeF{ terrain_thickness, room.right().length() }
	);

	createObject<Ground>(
		room.bottomCenter() + Vec2{ (generated_rooms.size() ? (passage_width / 2) : 0), (terrain_thickness / 2) },
		SizeF{ room.bottom().length() - (generated_rooms.size() ? passage_width : 0), terrain_thickness }
	);

	createObject<Terrain>(
		room.topCenter() - Vec2{ (passage_width / 2), (terrain_thickness / 2) },
		SizeF{ room.top().length() - passage_width, terrain_thickness }
	);

	createObject<Scaffold>(
		room.tr() - Vec2{ (passage_width / 2), (terrain_thickness / 2) },
		SizeF{ passage_width, terrain_thickness }
	);

	generated_rooms.push_back(room);
	generated_position = room.tr() - Vec2{ passage_width, terrain_thickness };
}

void Stage1::update()
{
	Stage::update();

	if (!generated_rooms.size())
	{
		generate(0);

		for (int i = 0; i < 4; i++) generate(Random(1, 3));
	}

	for (const auto& object : objects) if ((player = dynamic_cast<Player*>(object))) break;

	int32 player_max_hp = 0;
	int32 player_hp     = 0;

	static bool player_respawned = false;
	static bool player_spawn     = false;

	if (player)
	{
		player_max_hp = player->getMaxHP();
		player_hp     = player->getHP();

		if (P2Body& body = player->getBody())
		{
			double x = body.getPos().x;
			double y = body.getPos().y;

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
					enemy->setPlayerPosition(body.getPos());
				}
			}

			player_respawned = false;

			if (RectF(generated_position - Vec2{ 0, 10 }, SizeF{ 300, 10 }).intersects(body.getPos()))
			{
				sceneData().level++;
				sceneChange(SceneState::Game, 0.5s);
			}

			if (KeyL.down()) sceneData().level++;
			if (KeyK.down()) sceneData().level--;
		}
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
			createObject<Player>(generated_rooms[0].center());

			player_spawn = false;
		}
	}

	camera.update();

	PlayerHUD::GetInstance()->setPlayerHP(player_hp, player_max_hp);
}

void Stage1::draw() const
{
	Print << U"オブジェクト数: "     << objects   .size();
	Print << U"タイマーイベント数: " << GetTasks().size();
	Print << U"ステージレベル: "     << sceneData().level + 1;

	{
		const auto t2d = camera.createTransformer();

		for (const auto& room : generated_rooms) room.drawFrame(2, Palette::Red);

		RectF(generated_position - Vec2{ 0, 10 }, SizeF{ 300, 10 }).drawFrame(2, Palette::Blue);

		Stage::draw();
	}
}

void Stage1::NewInstance()
{
	DeleteInstance();

	instance = new Stage1();
}
