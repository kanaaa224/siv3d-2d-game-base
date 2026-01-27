# pragma once

# include "Stage.hpp"
# include "../Characters/Player.hpp"

class Stage1 : public Stage
{
public:
	Stage1();

	void update() override;
	void draw() const override;

	static void NewInstance();

private:
	Camera2D camera;

	Player* player;

	Vec2 generated_position;

	Array<RectF> generated_rooms;

	void generate(int32 template_index);
};
