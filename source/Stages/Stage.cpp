# include "Stage.hpp"

Stage* Stage::instance = nullptr;

Stage::Stage() : stepTime(1.0 / 200.0), accumulatedTime(0.0) {}

void Stage::update() {}

void Stage::draw() const {}

Stage* Stage::GetInstance()
{
	if (instance == nullptr) instance = new Stage();

	return instance;
}
