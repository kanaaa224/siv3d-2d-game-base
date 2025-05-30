# pragma once

# include <Siv3D.hpp>

class PlayerHUD
{
public:
	PlayerHUD();
	~PlayerHUD() = default;

	void update();
	void draw() const;

	void setPlayerHP(float hp, float max_hp) { player_hp = hp; player_max_hp = max_hp; }

	static PlayerHUD* GetInstance();

private:
	float player_hp, player_max_hp;

	static PlayerHUD* instance;
};
