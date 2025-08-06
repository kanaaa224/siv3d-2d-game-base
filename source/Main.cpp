# include "Common.hpp"
# include "Scenes/Title.hpp"
# include "Scenes/Game.hpp"

void AssetsRegistration()
{
	TextureAsset::Register({ U"Player",     { U"Player" } }, Emoji(U"🐈"));
	TextureAsset::Register({ U"Enemy 1",    { U"Enemy"  } }, Emoji(U"👻"));
	TextureAsset::Register({ U"Enemy 2",    { U"Enemy"  } }, Emoji(U"🌪️"));
	TextureAsset::Register({ U"Box 1",      { U"Object" } }, Emoji(U"🧱"));
	TextureAsset::Register({ U"Box 2",      { U"Object" } }, Emoji(U"⃣"));
	TextureAsset::Register({ U"Stage 1 BG", { U"Stage"  } }, U"example/texture/ground.jpg");
}

void Initialize()
{
	Window::Resize(1280, 720);

	Window::SetTitle(U"2Dゲームベース");
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
