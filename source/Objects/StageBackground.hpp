# pragma once

# include "ObjectBase.hpp"

class StageBackground : public ObjectBase
{
public:
	StageBackground(P2World& world, const Vec2& position = { 0, 0 });
	~StageBackground() = default;

	void draw() const override;
	
	void setCameraPosition(Vec2 pos = { 0, 0 }) { camera_position = pos; }
	
private:
	Vec2 camera_position;
};
