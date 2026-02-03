# pragma once

# include <Siv3D.hpp>

struct Effect5 : IEffect
{
	struct Particle
	{
		Vec2 offset, velocity;

		double size;
	};

	Vec2 position;

	Array<Particle> sparks;
	Array<Particle> smokes;
	Array<Particle> debris;

	explicit Effect5(const Vec2& position) : position(position)
	{
		for (int32 i = 0; i < 12; ++i) sparks << Particle{ RandomVec2(10.0), RandomVec2(300.0), Random(2.0, 5.0) };
		for (int32 i = 0; i <  8; ++i) smokes << Particle{ RandomVec2(20.0), RandomVec2(40.0), Random(20.0, 60.0) };
		for (int32 i = 0; i < 10; ++i) debris << Particle{ RandomVec2(5.0), Vec2{ Random(-150.0, 150.0), Random(-200.0, -50.0) }, Random(2.0, 4.0) };
	}

	bool update(double t = 0.0) override
	{
		const double e = EaseOutExpo(t);

		for (const auto& spark : sparks)
		{
			const Vec2 pos  = position + (spark.velocity * t * (1.0 - t * 0.5)) + (spark.offset);
			const Vec2 prev = pos - (spark.velocity * 0.02);

			Line{ prev, pos }.draw(spark.size * (1.0 - t), HSV{ 30, 0.8, 1.0, 1.0 - t });
		}

		for (const auto& smoke : smokes)
		{
			const Vec2 pos = position + (smoke.velocity * t) + (smoke.offset * e);

			Circle{ pos, smoke.size * (0.5 + t) }.draw(ColorF{ 0.2, 0.2, 0.2, (1.0 - t) * 0.4 });
		}

		for (const auto& d : debris)
		{
			const Vec2 gravity{ 0, 600.0 * t * t };
			const Vec2 pos = position + (d.velocity * t) + gravity + d.offset;

			Circle{ pos, d.size }.draw(HSV{ 20, 0.9, 1.0, 1.0 - t });
		}

		return (t < 1.0);
	}
};
