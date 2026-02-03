# pragma once

# include <Siv3D.hpp>

struct Effect3 : IEffect
{
	struct Spark
	{
		Vec2 offset, velocity;

		double lifetime;

		ColorF color;
	};

	Vec2 position, direction;

	Array<Spark> sparks;

	explicit Effect3(const Vec2& position, const Vec2& direction) : position(position), direction(direction)
	{
		double baseAngle = std::atan2(direction.y, direction.x);

		for (int i = 0; i < 10; ++i)
		{
			double speed = Random(100.0, 300.0);
			double angle = baseAngle + Random(-0.3, 0.3);

			Spark s;

			s.offset   = Vec2(0, 0);
			s.velocity = Vec2(std::cos(angle), std::sin(angle)) * speed;
			s.lifetime = Random(0.3, 0.6);
			s.color    = ColorF(1.0, Random(0.5, 1.0), 0.0);

			sparks.push_back(s);
		}
	}

	bool update(double /*t*/ = 0.0) override
	{
		double dt = Scene::DeltaTime();

		for (auto& s : sparks)
		{
			s.offset   += s.velocity * dt;
			s.lifetime -= dt;
			s.color.a   = Max(0.0, s.lifetime / 0.6);
		}

		for (auto& s : sparks) Circle(position + s.offset, 2.0).draw(s.color);

		return not sparks.all([](const Spark& s) { return s.lifetime <= 0.0; });
	}
};
