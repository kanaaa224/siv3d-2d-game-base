# pragma once

# include <Siv3D.hpp>

class GameUI
{
public:
	GameUI();
	~GameUI() = default;

	void update();
	void draw() const;

	void setPlayerHP(float hp) { player_hp = hp; }

	static GameUI* GetInstance();

private:
	float player_hp;

	static GameUI* instance;
};
