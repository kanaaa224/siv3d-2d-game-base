# pragma once

# include <Siv3D.hpp>

class ObjectBase
{
protected:
	P2Body body;

public:
	ObjectBase(P2World& world, const Vec2& position) { (void)world; (void)position;  }
	virtual ~ObjectBase() = default;

	virtual void update() {}
	virtual void draw() const {}

	virtual void onHit(ObjectBase& object) { (void)object; }

	P2Body& getBody() { return body; }
};
