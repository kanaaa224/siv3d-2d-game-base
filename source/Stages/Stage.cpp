# include "Stage.hpp"

Stage* Stage::instance = nullptr;

Stage::Stage() {}

void Stage::update() {}

void Stage::draw() const {}

Stage* Stage::GetInstance()
{
	if (instance == nullptr) instance = new Stage();

	return instance;
}
