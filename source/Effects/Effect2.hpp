# pragma once

# include <Siv3D.hpp>

struct Effect2 : IEffect
{
	Vec2   position;
	String text;
	Font   font;
	ColorF color;

	Effect2(const Vec2& position, const String& text = U"", const Font& font = Font{ 20 }, const ColorF& color = Palette::White) : position(position), text(text), font(font), color(color) {}

	bool update(double t = 0.0) override
	{
		ColorF c{ color, (1.0 - (t * 2.0)) };

		font(text).drawAt(TextStyle::Outline(0.2, ColorF{ 0.0, c.a }), font.fontSize(), position.movedBy(0, t * -120), c);

		return (t < 0.5);
	}
};
