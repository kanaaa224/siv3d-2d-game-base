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
	addObject<StageBackground>(Vec2{ 0, 0 });
	addObject<Player>(Vec2{ 320, 500 });

	floor = world.createRect(P2Static, Vec2{ 640, 600 }, SizeF{ 1000, 10 });
}

void Stage1::update()
{
	for (accumulatedTime += Scene::DeltaTime(); stepTime <= accumulatedTime; accumulatedTime -= stepTime)
	{
		world.update(stepTime);

		for (const auto& [pair, collision] : world.getCollisions())
		{
			ObjectBase* objectA = nullptr;
			ObjectBase* objectB = nullptr;

			for (const auto& object : objects)
			{
					 if (object->getBody().id() == pair.a) objectA = object;
				else if (object->getBody().id() == pair.b) objectB = object;

				if (objectA && objectB) break;
			}

			if (objectA && objectB)
			{
				auto* characterA = dynamic_cast<CharacterBase*>(objectA);
				auto* characterB = dynamic_cast<CharacterBase*>(objectB);

				if (characterA && characterB)
				{
					characterA->onHit(*characterB);
					characterB->onHit(*characterA);
				}
				else
				{
					objectA->onHit(*objectB);
					objectB->onHit(*objectA);
				}
			}
		}
	}

	auto _objects_ = objects;

	for (const auto& object : _objects_)
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
