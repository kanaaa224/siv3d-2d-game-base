# pragma once

# include "../Common.hpp"

class Title : public SM::Scene
{
public:
	Title(const InitData& init);

	void update() override;
	void draw() const override;
};
