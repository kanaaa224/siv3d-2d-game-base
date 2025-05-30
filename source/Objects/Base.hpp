# pragma once

# include "../Common.hpp"

class ObjectBase
{
public:
	ObjectBase(P2World& world, const Vec2& position) { (void)world; (void)position; }
	virtual ~ObjectBase() = default;

	virtual void update() {}
	virtual void draw() const {}

	virtual void onHit(ObjectBase& object) { (void)object; }

	P2Body& getBody() { return body; }

	virtual void destroy() { deleteSelf(); }

protected:
	P2Body body;

	void deleteSelf();
};
