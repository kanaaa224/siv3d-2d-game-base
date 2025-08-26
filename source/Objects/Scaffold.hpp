# pragma once

# include "ObjectBase.hpp"

class Scaffold : public ObjectBase
{
public:
	Scaffold(P2World& world, const Vec2& position = { 0, 0 });

	void draw() const override;

	virtual void onHit(ObjectBase& object, const P2Collision& collision) override;
};
