# pragma once

# include <Siv3D.hpp>

struct TouchEffect : IEffect
{
	struct Particle
	{
		Vec2 velocity, start;

		double r, angle;

		bool cw;

		ColorF color;
	};

	struct Star
	{
		Vec2 velocity, start;

		double angle, scale;

		ColorF color;
	};

	Vec2 m_pos;

	Array<Particle> m_particles;
	Array<Star>     m_stars;

	explicit TouchEffect(const Vec2& pos) :
		m_pos{ pos }
	{
		for (int32 i = 0; i < 200; ++i)
		{
			const Vec2 velocoty = RandomVec2(28.0);

			Particle particle{
				.velocity = velocoty,
				.start    = velocoty,

				.r     = Random(6.0, 12.0),
				.angle = Random(360_deg),
				.cw    = RandomBool(),

				.color = HSV{ Random(50.0, 70.0), 0.4, 1.0 },
			};

			m_particles << particle;
		}

		for (int32 i = 0; i < 8; ++i)
		{
			const Vec2 velocoty = RandomVec2(28.0);

			Star star{
				.velocity = velocoty,
				.start    = (velocoty + RandomVec2(2.0)),

				.angle = Random(360_deg),
				.scale = Random(0.6, 1.4),

				.color = HSV{ Random(50.0, 70.0), 0.4, 1.0 },
			};

			m_stars << star;
		}
	}

	bool update(double t) override
	{
		t /= 0.45;

		const double r = (30 + t * 30);
		const ColorF outer = HSV{ 180, 0.8, 1.0, 0.0 };
		const ColorF inner = HSV{ 180, 0.8, 1.0, (0.5 * (1.0 - t)) };

		Circle{ m_pos, r }
			.drawFrame(10, 0, outer, inner)
			.drawFrame(0, 10, inner, outer);

		for (const auto& particle : m_particles)
		{
			const Vec2 pos = m_pos
				+ particle.start
				+ Circular(particle.r, particle.angle + t * 120_deg * (particle.cw ? 1 : -1))
				+ (particle.velocity * t - 0.5 * t * t * particle.velocity);

			const double rOuter = (1.0 * (1.0 - t) * 2);
			const double rInner = (0.8 * (1.0 - t) * 2);

			Shape2D::NStar(2, rOuter, rInner, pos, particle.angle).draw(particle.color);
		}

		for (const auto& star : m_stars)
		{
			const Vec2 pos = m_pos
				+ star.start
				+ (star.velocity * t - 0.5 * t * t * star.velocity);

			const double rOuter = (12 * (1.0 - t) * star.scale);
			const double rInner = (4 * (1.0 - t) * star.scale);
			const double angle  = (star.angle + t * 90_deg);

			Shape2D::NStar(4, rOuter, rInner, pos, angle).draw(star.color);
		}

		return (t < 1.0);
	}
};
