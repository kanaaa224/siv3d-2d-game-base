# include "PlayerHUD.hpp"
# include "../Stages/Stage.hpp"

PlayerHUD* PlayerHUD::GetInstance()
{
	static PlayerHUD instance;

	return &instance;
}

void PlayerHUD::update() {}

void PlayerHUD::draw() const
{
	Print << U"Player HP: " << player_hp << U" / " << player_max_hp;

	if (SimpleGUI::Button(U"タイトルへ", Scene::Size() + Vec2{ -160, -(Scene::Height() - 10) }, 150)) Stage::GetInstance()->sceneChange(SceneState::Title, 0.5s);
}

void PlayerHUD::setPlayerHP(float hp, float max_hp)
{
	player_hp     = hp;
	player_max_hp = max_hp;
}
