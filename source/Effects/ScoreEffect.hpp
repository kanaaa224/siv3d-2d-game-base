# pragma once

# include <Siv3D.hpp>

struct ScoreEffect : IEffect
{
	Vec2  m_start;
	int32 m_score;
	Font  m_font;

	ScoreEffect(const Vec2& start, int32 score, const Font& font) :
		m_start{ start },
		m_score{ score },
		m_font { font }
	{}

	bool update(double t) override
	{
		const HSV color{ (180 - m_score * 1.8), (1.0 - (t * 2.0)) };

		m_font(m_score).drawAt(TextStyle::Outline(0.2, ColorF{ 0.0, color.a }), 40, m_start.movedBy(0, t * -120), color);

		return (t < 0.5);
	}
};
