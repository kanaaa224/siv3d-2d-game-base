﻿# include "Stage.hpp"

Stage::Stage() : stepTime(1.0 / 200.0), accumulatedTime(0.0) {}

Stage::~Stage()
{
	for (const auto& object : objects) delete object;

	objects.clear();
	deletionObjects.clear();
}

void Stage::update()
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
				objectA->onHit(*objectB, collision);
				objectB->onHit(*objectA, collision);
			}
		}
	}

	auto _objects_ = objects;

	for (const auto& object : _objects_) object->update();

	if (!deletionObjects.isEmpty())
	{
		objects.remove_if([this](ObjectBase* object)
		{
			if (deletionObjects.contains(object))
			{
				delete object;

				return true;
			}

			return false;
		});

		deletionObjects.clear();
	}
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
