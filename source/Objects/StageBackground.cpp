# include "StageBackground.hpp"

StageBackground::StageBackground(P2World& world, const Vec2& position) : ObjectBase(world, position)
{
	this->initialize();
}

StageBackground::~StageBackground()
{
	this->finalize();
}

void StageBackground::initialize()
{

}

void StageBackground::update()
{

}

void StageBackground::draw() const
{
	TextureAsset(U"Stage 1 Background").resized(Scene::Size()).draw(body.getPos());
}

void StageBackground::finalize()
{

}
