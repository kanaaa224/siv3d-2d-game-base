# include "StageBackground.hpp"

StageBackground::StageBackground(P2World& world, const Vec2& position) : ObjectBase(world, position) {}

void StageBackground::draw() const
{
	const auto texture = TextureAsset(U"Stage 1 Background").resized(Scene::Size());

	const int width  = Scene::Width();
	const int height = Scene::Height();

	const int baseX = static_cast<int>(std::floor(camera_position.x / width )) * width;
	const int baseY = static_cast<int>(std::floor(camera_position.y / height)) * height;

	for (int y = -1; y <= 2; ++y)
	{
		for (int x = -1; x <= 2; ++x)
		{
			texture.draw(baseX + x * width, baseY + y * height);
		}
	}
}
