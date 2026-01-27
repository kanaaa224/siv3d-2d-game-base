# pragma once

# include "ObjectBase.hpp"

# define SCAFFOLD_DEFAULT_SIZE SizeF{ 500, 10 }

class Scaffold : public ObjectBase
{
public:
	Scaffold(P2World& world, const Vec2& position = { 0, 0 }, const SizeF& size = SCAFFOLD_DEFAULT_SIZE, bool passThrough = true);

	void draw() const override;

	virtual void onHit(ObjectBase& object, const P2Collision& collision) override;

	bool canPassThrough() const { return pass_through; }

private:
	bool pass_through;
};
