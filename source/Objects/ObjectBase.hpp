# pragma once

# include "../Common.hpp"

class ObjectBase
{
public:
	ObjectBase(P2World& world, const Vec2& position) { (void)world; (void)position; }
	virtual ~ObjectBase() = default;

	virtual void update() {}
	virtual void draw() const {}

	P2Body& getBody() { return body; }

	virtual void destroy() { deleteSelf(); }

	virtual void handleCollision(ObjectBase& object, const P2Collision& collision) { onCollision(object, collision); }

protected:
	P2Body body;

	void deleteSelf();

	virtual void onCollision(ObjectBase& object, const P2Collision& collision) { (void)object; (void)collision; }
};
