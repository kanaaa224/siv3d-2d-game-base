# pragma once

# include <Siv3D.hpp>

class HPBar
{
public:
	HPBar() = default;

	struct Style
	{
		ColorF backgroundColor{ 0.0, 0.6 };
		ColorF delayColor{ 0.9, 0.8, 0.3 };
		ColorF hpColor{ 0.8, 0.2, 0.2 };
		ColorF frameColor{ 0.1 };

		double frameThickness = 1.5;
	};

	explicit constexpr HPBar(int32 maxHP) noexcept
		: m_maxHP{ maxHP }
		, m_currentHP{ maxHP }
		, m_delayHP{ static_cast<double>(m_currentHP) } {
	}

	constexpr HPBar(int32 maxHP, int32 currentHP) noexcept
		: m_maxHP{ maxHP }
		, m_currentHP{ currentHP }
		, m_delayHP{ static_cast<double>(m_currentHP) } {
	}

	void update(double smoothTimeSec = 0.4)
	{
		m_delayHP = Math::SmoothDamp(m_delayHP, m_currentHP, m_delayVelocity, smoothTimeSec);
	}

	void draw(const RectF& rect) const
	{
		draw(rect, Style{});
	}

	void draw(const RectF& rect, const Style& style) const
	{
		const RectF rectDelay{ rect.pos, (rect.w * getDelayHPRatio()), rect.h };
		const RectF rectHP{ rect.pos, (rect.w * getHPRatio()), rect.h };

		rect.draw(style.backgroundColor);
		rectDelay.draw(style.delayColor);
		rectHP.draw(style.hpColor);
		rect.drawFrame(style.frameThickness, style.frameColor);
	}

	void drawHex(const RectF& rect) const
	{
		drawHex(rect, Style{});
	}

	void drawHex(const RectF& rect, const Style& style) const
	{
		const RectF rectDelay{ rect.pos, (rect.w * getDelayHPRatio()), rect.h };
		const RectF rectHP{ rect.pos, (rect.w * getHPRatio()), rect.h };
		const Polygon hex = MakeHexPolygon(rect);

		hex.draw(style.backgroundColor);

		for (const auto& shape : Geometry2D::And(hex, rectDelay))
		{
			shape.draw(style.delayColor);
		}

		for (const auto& shape : Geometry2D::And(hex, rectHP))
		{
			shape.draw(style.hpColor);
		}

		hex.drawFrame(style.frameThickness, style.frameColor);
	}

	[[nodiscard]]
	constexpr int32 getHP() const noexcept
	{
		return m_currentHP;
	}

	[[nodiscard]]
	constexpr int32 getMaxHP() const noexcept
	{
		return m_maxHP;
	}

	[[nodiscard]]
	constexpr double getHPRatio() const noexcept
	{
		return (static_cast<double>(m_currentHP) / m_maxHP);
	}

	constexpr void setHP(int32 hp) noexcept
	{
		m_currentHP = Clamp(hp, 0, m_maxHP);
		m_delayHP = m_currentHP;
		m_delayVelocity = 0.0;
	}

	constexpr void setMaxHP(int32 hp) noexcept
	{
		m_maxHP = hp;
	}

	constexpr void damage(int32 damage) noexcept
	{
		m_currentHP = Clamp((m_currentHP - damage), 0, m_maxHP);
	}

	constexpr void heal(int32 heal) noexcept
	{
		setHP(m_currentHP + heal);
	}

private:
	int32 m_maxHP = 1;
	int32 m_currentHP = 1;

	double m_delayHP = 1;
	double m_delayVelocity = 0.0;

	[[nodiscard]]
	constexpr double getDelayHPRatio() const noexcept
	{
		return (m_delayHP / m_maxHP);
	}

	[[nodiscard]]
	static Polygon MakeHexPolygon(const RectF& rect)
	{
		const Vec2 offsetH{ (rect.h * 0.5), 0.0 };
		const Vec2 offsetV{ 0.0, (rect.h * 0.5) };

		return Polygon{ { (rect.tl() + offsetH), (rect.tr() - offsetH), (rect.tr() + offsetV), (rect.br() - offsetH), (rect.bl() + offsetH), (rect.tl() + offsetV) } };
	}
};
