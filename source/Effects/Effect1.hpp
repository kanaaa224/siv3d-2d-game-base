# pragma once

# include <Siv3D.hpp>

struct Effect1 : IEffect
{
	struct Bubble
	{
		Vec2 offset;

		double startTime, scale;

		ColorF color;
	};

	Vec2 position;

	Array<Bubble> bubbles;

	Effect1(const Vec2& position, double baseHue = Random(0.0, 360.0)) : position(position)
	{
		for (int32 i = 0; i < 8; ++i)
		{
			Bubble bubble{
				.offset    = RandomVec2(Circle(30)),
				.startTime = Random(-0.3, 0.1),
				.scale     = Random( 0.1, 1.2),

				.color = HSV{ baseHue + Random(-30.0, 30.0) }
			};

			bubbles << bubble;
		}
	}

	bool update(double t = 0.0) override
	{
		for (const auto& bubble : bubbles)
		{
			const double t2 = (bubble.startTime + t);

			if (not InRange(t2, 0.0, 1.0)) continue;

			const double e = EaseOutExpo(t2);

			Circle{ (position + bubble.offset + (bubble.offset * 4 * t)), (e * 40 * bubble.scale) }
				.draw(ColorF{ bubble.color, 0.15 })
				.drawFrame((30.0 * (1.0 - e) * bubble.scale), bubble.color);
		}

		return (t < 1.3);
	}
};
