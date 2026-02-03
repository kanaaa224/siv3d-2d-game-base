# include "EnemyBase.hpp"
# include "../Effects/Effect1.hpp"
# include "../Effects/Effect2.hpp"
# include "../Utils/TimerUtils.hpp"

using namespace TimerUtils;

EnemyBase::EnemyBase(P2World& world, const Vec2& position) : CharacterBase(world, position), current_position(position), start_position(position), damaged(false)
{
	effect.add<Effect1>(start_position);
}

void EnemyBase::update()
{
	if (body) current_position = body.getPos();

	if (current_position.y >= (Scene::Height() + 100)) die();

	hpBar.damage(hpBar.getHP() - (int32)hp);
	hpBar.update();

	if (KeyE.down()) applyDamage(25);
}

void EnemyBase::draw() const
{
	static Font font{ 12 };

	if (body)
	{
		font(hp).drawAt(current_position + Vec2{0, -85}, Palette::White);

		hpBar.draw({ current_position + Vec2{ -35, -75 }, SizeF{ 70.0, 7.5 } });
	}

	effect.update();

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void EnemyBase::onDamaged(int32 amount)
{
	if (not damaged)
	{
		addHP(-amount);

		if (hp)
		{
			SetTimeout([this] { damaged = false; }, 500ms);
		}
		else
		{
			body.release();

			SetTimeout([this] { if (this) die(); }, 3s);
		}

		damaged = true;

		effect.add<Effect2>(current_position + Vec2{ 0, -75 }, Format(amount), Font{ 28, Typeface::Heavy, FontStyle::Italic }, HSV{ 180 - amount * 1.8 });
	}
}
