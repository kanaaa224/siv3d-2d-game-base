# include "Common.hpp"
# include "Scenes/Title.hpp"
# include "Scenes/Game.hpp"

void AssetsRegistration()
{
	FontAsset::Register(U"Title", FontMethod::MSDF, 48, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset::Register(U"Bold",  FontMethod::MSDF, 48, Typeface::Bold);

	FontAsset(U"Title").setBufferThickness(4);

	TextureAsset::Register({ U"Player",             { U"Player" } }, Emoji(U"🐈"));
	TextureAsset::Register({ U"Enemy 1",            { U"Enemy"  } }, Emoji(U"👻"));
	TextureAsset::Register({ U"Enemy 2",            { U"Enemy"  } }, Emoji(U"🌪️"));
	TextureAsset::Register({ U"Box 1",              { U"Object" } }, Emoji(U"🧱"));
	TextureAsset::Register({ U"Box 2",              { U"Object" } }, Emoji(U"⃣"));
	TextureAsset::Register({ U"Stage 1 Background", { U"Stage"  } }, U"example/texture/ground.jpg");
}

void Initialize()
{
	Window::Resize(1280, 720);

	Window::SetTitle(U"タイトル");
}

void Main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	AssetsRegistration();

	Initialize();

	SM sceneManager;

	sceneManager.add<Title>(SceneState::Title);
	sceneManager.add<Game> (SceneState::Game);
	sceneManager.init      (SceneState::Title, 0.5s);

	while (System::Update()) if (not sceneManager.update()) break;
}
