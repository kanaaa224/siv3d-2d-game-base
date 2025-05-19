# pragma once

# include "ObjectBase.hpp"

class StageBackground : public ObjectBase
{
public:
	StageBackground(P2World& world, const Vec2& position);
	~StageBackground();

	void update() override;
	void draw() const override;

private:
	void initialize();
	void finalize();
};
