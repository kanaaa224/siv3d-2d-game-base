# include "Punipuni.hpp"

namespace
{
	Array<Vec2> ChaikinSmooth(const Array<Vec2>& inputVertices, int iterations = 2)
	{
		if (inputVertices.size() < 3) throw std::invalid_argument("Input vertices must form a polygon (at least 3 vertices).");
		if (iterations <= 0)          throw std::invalid_argument("Iterations must be a positive integer.");

		Array<Vec2> currentVertices = inputVertices;

		for (int k = 0; k < iterations; ++k)
		{
			Array<Vec2> newVertices;

			const size_t vertexCount = currentVertices.size();

			for (size_t i = 0; i < vertexCount; ++i)
			{
				const Vec2& p0 = currentVertices[i];
				const Vec2& p1 = currentVertices[(i + 1) % vertexCount];

				const Vec2 q = p0 * 0.75 + p1 * 0.25;
				const Vec2 r = p0 * 0.25 + p1 * 0.75;

				newVertices << q << r;
			}

			currentVertices = newVertices;
		}

		return currentVertices;
	}
}

Punipuni::Punipuni(P2World& world, const Vec2& position) : ObjectBase(world, position), centerRadius(25.0), outerRadius(15.0)
{
	P2Material material { .friction = 0.5 };

	body = world.createCircle(P2Dynamic, position, Circle(centerRadius), material);

	const int32 num = 12;

	const double diffAngle = Math::TwoPi / num;

	for (int32 i = 0; i < num; ++i)
	{
		const Vec2 offset = Vec2::Right().rotated(diffAngle * i) * (centerRadius + outerRadius);

		aroundBodies << world.createCircle(P2Dynamic, position + offset, Circle(outerRadius), material);
	}

	for (int32 i = 0; i < num; ++i)
	{
		const Vec2 jointPosA = body.getPos();
		const Vec2 jointPosB = aroundBodies[i].getPos();

		joints << world.createDistanceJoint(body, jointPosA, aroundBodies[i], jointPosB, (jointPosB - jointPosA).length()).setLinearStiffness(3.0, 0.5).setMinLength(0.0);
	}

	for (int32 i = 0; i < num; ++i)
	{
		const Vec2& posA = aroundBodies[i].getPos();
		const Vec2& posB = aroundBodies[(i + 1) % num].getPos();

		joints << world.createDistanceJoint(aroundBodies[i], posA, aroundBodies[(i + 1) % num], posB, (posB - posA).length()).setLinearStiffness(1.0, 0.5).setMinLength(0.0);
	}
}

void Punipuni::update()
{
	if (body.getPos().y >= (Scene::Height() + 100)) deleteSelf();
	
	if (KeyU.down()) body.applyLinearImpulse({ 0, -500 });
}

void Punipuni::draw() const
{
	Array<Vec2> vertices;

	for (const auto& b : aroundBodies) vertices << b.getPos();

	Polygon(ChaikinSmooth(vertices)).calculateBuffer(outerRadius).drawFrame();
}
