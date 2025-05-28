# include "Common.hpp"
# include "Scene/Title.hpp"
# include "Scene/Game.hpp"

void AssetsRegistration()
{
	// アセットの登録
	FontAsset::Register(U"Title", FontMethod::MSDF, 48, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset::Register(U"Bold", FontMethod::MSDF, 48, Typeface::Bold);

	FontAsset(U"Title").setBufferThickness(4);

	TextureAsset::Register({ U"Player", { U"Player" } }, U"example/siv3d-kun.png");
	TextureAsset::Register({ U"Stage 1 Background", { U"Stage" } }, U"example/bay.jpg");
}

void Initialize()
{
	Window::Resize(1280, 720);

	Window::SetTitle(U"タイトル");
}

void Main()
{
	AssetsRegistration();

	Initialize();

	App manager;

	manager.add<Title>(SceneState::Title);
	manager.add<Game>(SceneState::Game);

	manager.init(SceneState::Title, 0.5s);

	while (System::Update())
	{
		if (not manager.update()) break;
	}
}
