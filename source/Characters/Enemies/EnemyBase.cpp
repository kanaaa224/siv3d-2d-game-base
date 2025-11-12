# include "EnemyBase.hpp"
# include "../../Effects/BubbleEffect.hpp"
# include "../../Effects/ScoreEffect.hpp"
# include "../../Utils/TimerUtils.hpp"

using namespace TimerUtils;

EnemyBase::EnemyBase(P2World& world, const Vec2& position) : CharacterBase(world, position), start_position(position), damaged(false)
{
	initialize();
}

void EnemyBase::initialize()
{
	hp = max_hp = ENEMY_MAX_HP;

	effect.add<BubbleEffect>(start_position, Random(0.0, 360.0));
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
	if (body) hpBar.draw({ current_position + Vec2{ -35, -75 }, SizeF{ 70, 7.5 } });

	effect.update();

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void EnemyBase::onDamaged(float amount)
{
	if (!damaged)
	{
		addHP(-amount);

		if (hp)
		{
			SetTimeout([this] { damaged = false; }, 500ms);
		}
		else
		{
			body.release();

			SetTimeout([this] { die(); }, 3s);
		}

		damaged = true;

		static Font font{ FontMethod::MSDF, 48, Typeface::Heavy, FontStyle::Italic };

		effect.add<ScoreEffect>(current_position + Vec2{ 0, -75 }, (int)amount, font);
	}
}
