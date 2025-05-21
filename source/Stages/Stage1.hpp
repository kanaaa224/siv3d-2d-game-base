# pragma once

# include "Stage.hpp"

class Stage1 : public Stage
{
public:
	Stage1();
	~Stage1() = default;

	void update() override;
	void draw() const override;

	static void NewInstance();

private:
	P2Body floor;

	void initialize();
};
