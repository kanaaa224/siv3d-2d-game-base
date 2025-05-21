# pragma once

# include "ObjectBase.hpp"

class Box1 : public ObjectBase
{
public:
	Box1(P2World& world, const Vec2& position);
	~Box1();

	void update() override;
	void draw() const override;

private:
	void initialize();
	void finalize();
};
