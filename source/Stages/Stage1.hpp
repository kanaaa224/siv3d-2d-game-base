# pragma once

# include "Stage.hpp"

class Stage1 : public Stage
{
public:
	Stage1();

	void update() override;
	void draw() const override;

	static void NewInstance();

private:
	P2Body floor;

	Camera2D camera;

	void initialize();
};
