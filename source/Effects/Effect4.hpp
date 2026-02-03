# pragma once

# include <Siv3D.hpp>

struct Particle
{
	Vec2 start, velocity;
};

struct Effect4 : IEffect
{
	Array<Particle> particles;

	explicit Effect4(const Vec2& position) : particles(Random(10, 25))
	{
		for (auto& particle : particles)
		{
			particle.start    = (position + RandomVec2(12.0));
			particle.velocity = (RandomVec2(1.0) * Random(100.0));
		}
	}

	bool update(double t = 0.0) override
	{
		for (const auto& particle : particles)
		{
			const Vec2 pos = (particle.start + particle.velocity * t + 0.5 * t * t * Vec2{ 0, 240 });

			Triangle{ pos, (20.0 * (1.0 - t)), (pos.x * 10_deg) }.draw(HSV{ pos.y - 40 });
		}

		return (t < 1.0);
	}
};
