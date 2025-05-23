# pragma once

# include <Siv3D.hpp>

class GameUI
{
public:
	GameUI();
	~GameUI();

	void update();
	void draw() const;

	void setPlayerHP(float hp) { player_hp = hp; }

	static GameUI* GetInstance();

private:
	float player_hp;

	void initialize();
	void finalize();

	static GameUI* instance;
};
