# include "Title.hpp"

Title::Title(const InitData& init) : IScene{ init } {}

void Title::update()
{
	{
		m_startTransition.update(m_startButton.mouseOver());
		m_exitTransition .update(m_exitButton .mouseOver());

		if (m_startButton.mouseOver() || m_exitButton.mouseOver()) Cursor::RequestStyle(CursorStyle::Hand);
	}

	     if (m_startButton.leftClicked()) changeScene(SceneState::Game, 0.5s);
	else if (m_exitButton .leftClicked()) System::Exit();
}

void Title::draw() const
{
	Scene::SetBackground(ColorF{ 0.5 });

	FontAsset(U"Title")(U"タイトル").drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.1, 0.1, 0.1 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 50, (Scene::Center() + Vec2{ 0, -100 }));

	{
		m_startButton.draw(ColorF{ 1.0, m_startTransition.value() }).drawFrame(1);
		m_exitButton .draw(ColorF{ 1.0, m_exitTransition .value() }).drawFrame(1);

		const Font& boldFont = FontAsset(U"Bold");

		boldFont(U"PLAY").drawAt(25, m_startButton.center(), ColorF{ 0.1 });
		boldFont(U"EXIT").drawAt(25, m_exitButton .center(), ColorF{ 0.1 });
	}
}
