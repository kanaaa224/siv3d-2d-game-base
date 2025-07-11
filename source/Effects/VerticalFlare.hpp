# pragma once

# include <Siv3D.hpp>

struct VerticalFlare : IEffect
{
	Vec2 m_pos;

	Texture m_texture;

	VerticalFlare(const Vec2& pos, const Texture& texture) :
		m_pos    { pos },
		m_texture{ texture }
	{}

	bool update(double t) override
	{
		t /= 0.5;

		const double e     = EaseInSine(t);
		const double scale = 6.0 * (1.0 - e);

		double s = 1.0;

		for (auto i : step(9))
		{
			m_texture.scaled(scale * Vec2{ s, (1.0 / s) }).drawAt(m_pos, HSV{ (120 * i), 0.4 });

			s *= 1.25;
		}

		return (t < 1.0);
	}
};
