# pragma once

# include "ObjectBase.hpp"

class StageBackground : public ObjectBase
{
public:
	StageBackground(P2World& world, const Vec2& position = { 0, 0 });

	void draw() const override;

	void setCameraPosition(const Vec2& position = { 0, 0 }) { camera_position = position; }

private:
	Vec2 camera_position;
};
