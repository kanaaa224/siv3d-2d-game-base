# pragma once

# include "ObjectBase.hpp"

class Punipuni : public ObjectBase
{
public:
	Punipuni(P2World& world, const Vec2& position = { 0, 0 });
	~Punipuni() = default;

	void update() override;
	void draw() const override;

private:
	Array<P2Body> aroundBodies;
	Array<P2DistanceJoint> joints;

	double centerRadius;
	double outerRadius;
};
