# pragma once

# include "Base.hpp"

class StageBackground : public ObjectBase
{
public:
	StageBackground(P2World& world, const Vec2& position);
	~StageBackground() = default;

	void draw() const override;
};
