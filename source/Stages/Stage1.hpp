# pragma once

# include "stage.hpp"

class Stage1 : public Stage
{
public:
	Stage1();
	~Stage1();

	void update() override;
	void draw() const override;

	static Stage1* GetInstance();

private:
	static Stage1* instance;

	P2Body floor;

	void initialize();
	void finalize();
};
