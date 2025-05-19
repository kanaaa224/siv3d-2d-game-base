# pragma once

class GameUI
{
public:
	GameUI();
	~GameUI();

	void update();
	void draw()const;

	static GameUI* GetInstance();

private:
	static GameUI* instance;

	void initialize();
	void finalize();
};
