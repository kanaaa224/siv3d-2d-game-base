# include "Title.hpp"

Title::Title(const InitData& init) : IScene{ init }
{
	Window::SetStyle(WindowStyle::Sizable);

	Scene::SetBackground(ColorF{ 0.25 });
}

void Title::update()
{
	if (SimpleGUI::Button(U"プレイ", Scene::Center() + Vec2{ -100, -45 }, 200) || KeyEnter.down()) changeScene(SceneState::Game, 0.5s);
	if (SimpleGUI::Button(U"終了",   Scene::Center() + Vec2{ -100,   5 }, 200) || KeyE    .down()) System::Exit();

	if (KeyF.down()) Window::SetFullscreen(!Window::GetState().fullscreen);
	if (KeyM.down()) Window::Maximize();
	if (KeyR.down()) Window::Restore();
}

void Title::draw() const
{
	ClearPrint();
}
