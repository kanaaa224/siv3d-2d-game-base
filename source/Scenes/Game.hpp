# pragma once

# include "../Common.hpp"

class Game : public SM::Scene
{
public:
	Game(const InitData& init);

	void update() override;
	void draw() const override;
};
