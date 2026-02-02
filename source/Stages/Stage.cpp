# include "Stage.hpp"

Stage::Stage() : step_time(1.0 / 200.0), accumulated_time(0.0) {}

Stage::~Stage()
{
	for (const auto& object : objects) delete object;

	objects         .clear();
	objects_deletion.clear();
}

void Stage::update()
{
	for (accumulated_time += Scene::DeltaTime(); step_time <= accumulated_time; accumulated_time -= step_time)
	{
		world.update(step_time);

		for (const auto& [pair, collision] : world.getCollisions())
		{
			ObjectBase* objectA = nullptr;
			ObjectBase* objectB = nullptr;

			for (const auto& object : objects)
			{
				if (!object->getBody()) continue;

				     if (object->getBody().id() == pair.a) objectA = object;
				else if (object->getBody().id() == pair.b) objectB = object;

				if (objectA && objectB) break;
			}

			if (objectA && objectB)
			{
				objectA->handleCollision(*objectB, collision);
				objectB->handleCollision(*objectA, collision);
			}
		}
	}

	if (!objects_deletion.isEmpty())
	{
		objects.remove_if([this](ObjectBase* object)
		{
			if (!objects_deletion.contains(object)) return false;

			delete object;

			return true;
		});

		objects_deletion.clear();
	}

	Array<ObjectBase*> snapshot = objects;

	for (const auto& object : snapshot) object->update();
}

void Stage::draw() const
{
	for (const auto& object : objects) object->draw();
}

Stage* Stage::instance = nullptr;

void Stage::DeleteInstance()
{
	if (instance != nullptr)
	{
		delete instance;

		instance = nullptr;
	}
}

void Stage::NewInstance()
{
	DeleteInstance();

	instance = new Stage();
}

Stage* Stage::GetInstance()
{
	if (instance == nullptr) NewInstance();

	return instance;
}
