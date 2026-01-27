# include "StageBackground.hpp"

StageBackground::StageBackground(P2World& world, const Vec2& position) : ObjectBase(world, position) {}

void StageBackground::draw() const
{
	const SizeF scene_size = Scene::Size();
	const RectF area{ camera_position - scene_size / 2, scene_size * 2 };

	area.draw(Arg::top = ColorF{ 0.02, 0.02, 0.05 }, Arg::bottom = ColorF{ 0.05, 0.05, 0.1 });

	const double grid   = 120.0;
	const double startX = Math::Floor(area.x / grid) * grid;
	const double startY = Math::Floor(area.y / grid) * grid;

	for (double y = startY; y < area.y + area.h; y += grid)
	{
		for (double x = startX; x < area.x + area.w; x += grid)
		{
			const RectF cell{ x, y, grid, grid };

			cell.drawFrame(1.0, ColorF{ 0.2, 0.4, 0.8, 0.2 });

			Circle{ x, y, 1.5 }.draw(ColorF{ 0.4, 0.7, 1.0, 0.5 });

			if (Math::Fraction(x * 0.123 + y * 0.456) > 0.8) RectF{ x + 10, y + 10, 4, 4 }.draw(ColorF{ 0.3, 0.6, 1.0, 0.3 });
		}
	}
}
