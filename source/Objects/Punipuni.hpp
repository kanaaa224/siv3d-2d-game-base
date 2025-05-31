# pragma once

# include "Base.hpp"

class Punipuni : public ObjectBase
{
public:
	Punipuni(P2World& world, const Vec2& position);
	~Punipuni() = default;

	void update() override;
	void draw() const override;
	
private:
	Array<P2Body> aroundBodies;
	Array<P2DistanceJoint> joints;

	double centerRadius;
	double outerRadius;
};
