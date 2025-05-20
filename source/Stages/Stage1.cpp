# include "Stage1.hpp"

# include "../Objects/GameUI.hpp"
# include "../Objects/Player.hpp"
# include "../Objects/StageBackground.hpp"

Stage1* Stage1::instance = nullptr;

Stage1::Stage1()
{
	this->initialize();
}

Stage1::~Stage1()
{
	this->finalize();
}

void Stage1::initialize()
{
	objects << new StageBackground(world, Vec2{ 0, 0 });
	objects << new Player(world, Vec2{ 320, 500 });

	floor = world.createRect(P2Static, Vec2{ 640, 600 }, SizeF{ 1000, 10 });
}

void Stage1::update()
{
	constexpr double StepTime = (1.0 / 200.0);

	double accumulatedTime = 0.0;

	for (accumulatedTime += Scene::DeltaTime(); StepTime <= accumulatedTime; accumulatedTime -= StepTime)
	{
		world.update(StepTime);
	}

	for (const auto& object : objects)
	{
		object->update();
	}

	GameUI* gameUI = GameUI::GetInstance();

	gameUI->update();
}

void Stage1::draw() const
{
	ClearPrint();

	for (const auto& object : objects)
	{
		object->draw();
	}

	floor.draw();

	GameUI* gameUI = GameUI::GetInstance();

	gameUI->draw();
}

void Stage1::finalize()
{
	for (const auto& object : objects)
	{
		delete object;
	}
}

Stage1* Stage1::GetInstance()
{
	if (instance == nullptr) instance = new Stage1();

	return instance;
}
