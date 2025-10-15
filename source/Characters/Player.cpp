# include "Player.hpp"
# include "Enemies/Enemy1.hpp"
# include "Enemies/Enemy2.hpp"
# include "../Stages/Stage.hpp"
# include "../Objects/Boxes/Box1.hpp"
# include "../Objects/Boxes/Box2.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Objects/Bullet.hpp"
# include "../Effects/ScoreEffect.hpp"
# include "../Utils/TimerUtils.hpp"

using namespace TimerUtils;

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position), start_position(position), damaged(false)
{
	body = world.createPolygon(
		P2Dynamic,
		position,
		Polygon{
			{
				Vec2{ -10,  50 }, Vec2{ -30,  30 }, Vec2{ -30, -30 }, Vec2{ -10, -50 },
				Vec2{  10, -50 }, Vec2{  30, -30 }, Vec2{  30,  30 }, Vec2{  10,  50 }
			}
		},
		P2Material{
			.friction = 0.5
		},
		P2Filter{
			.categoryBits = CollisionCategory::Player,
			.maskBits     = CollisionCategory::All & ~CollisionCategory::Bullet
		}
	);

	body.setFixedRotation(true);

	initialize();
}

void Player::initialize()
{
	hp = max_hp = PLAYER_MAX_HP;
}

void Player::update()
{
	if (body) current_position = body.getPos();

	handleInput();

	if (current_position.y >= (Scene::Height() + 100)) die();
}

void Player::draw() const
{
	Line(body.getPos(), body.getPos() + aim * 100).draw();

	static bool mirrored = false;

	if (not InRange(body.getVelocity().x, -1.0, 1.0)) mirrored = body.getVelocity().x > 0.0;

	TextureAsset(U"Player").mirrored(mirrored).resized({ 105, 105 }).rotated(body.getAngle()).drawAt(body.getPos(), damaged ? ColorF{ 1.0, 0.25, 0.25, 0.5 } : ColorF{ 1.0 });

	effect.update();

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void Player::onHit(ObjectBase& object, const P2Collision& collision)
{
	if (Enemy1* enemy1 = dynamic_cast<Enemy1*>(&object))
	{
		if (Abs((body.getPos().y + 50) - collision.contact(0).point.y) < 10.0)
		{
			int damage = Random(70, 90);

			enemy1->applyDamage((float)damage);

			static Font font{ FontMethod::MSDF, 48, Typeface::Heavy, FontStyle::Italic };

			effect.clear();
			effect.add<ScoreEffect>(collision.contact(0).point, damage, font);
		}
	}
}

void Player::onDamaged(float amount)
{
	if (!damaged)
	{
		CharacterBase::onDamaged(amount);

		SetTimeout([this] { damaged = false; }, 750ms);

		damaged = true;
	}
}

void Player::handleInput()
{
	if (KeyA.pressed()) moveLeft();
	if (KeyD.pressed()) moveRight();

	Duration d = KeySpace.pressedDuration();

	if (d <= 0ms) d = KeyW.pressedDuration();

	if (KeyS.down()) descendScaffold();

	if (KeyM.down() || MouseL.down()) shoot();

	size_t playerIndex = 0;

	auto controller = XInput(playerIndex);

	if (controller.isConnected())
	{
		const double stickDeadZone = 0.2;

		if (controller.buttonLeft .pressed() || controller.leftThumbX < -stickDeadZone) moveLeft();
		if (controller.buttonRight.pressed() || controller.leftThumbX >  stickDeadZone) moveRight();

		if (d <= 0ms) d = controller.buttonA .pressedDuration();
		if (d <= 0ms) d = controller.buttonUp.pressedDuration();
		if (d <= 0ms) if (controller.leftThumbY > stickDeadZone) jump();

		if (controller.buttonY.down() || controller.buttonDown.down() || controller.leftThumbY < -stickDeadZone) descendScaffold();

		if (controller.buttonLB.down() || controller.buttonRB.down()) shoot();

		Vec2 stickAim{ controller.rightThumbX, -controller.rightThumbY };

		if (stickAim.length() > stickDeadZone) aim = stickAim.normalized();
	}
	else
	{
		Vec2 cursorPos = Cursor::PosF();

		if (stage_camera) cursorPos = stage_camera->getMat3x2().inverse().transformPoint(cursorPos);

		aim = (cursorPos - body.getPos()).normalized();
	}

	if (d > 0ms && d <= PLAYER_MAX_JUMP_HOLD) jump(d < PLAYER_MIN_JUMP_HOLD ? 0.5 : 1.0);

	if (Key1.pressed()) Stage::GetInstance()->createObject<Box1>    (Vec2{ (Scene::Width() / 2), 0 });
	if (Key2.pressed()) Stage::GetInstance()->createObject<Box2>    (Vec2{ (Scene::Width() / 2), 0 });
	if (Key3.pressed()) Stage::GetInstance()->createObject<Punipuni>(Vec2{ (Scene::Width() / 2), 0 });
	if (Key4.pressed()) Stage::GetInstance()->createObject<Enemy1>  (Vec2{ (Scene::Width() / 2), 0 });
	if (Key5.pressed()) Stage::GetInstance()->createObject<Enemy2>  (Vec2{ (Scene::Width() / 2), 0 });

	if (KeyQ.down()) Stage::GetInstance()->sceneChange(SceneState::Title, 0.5s);
	if (KeyH.down()) heal(10);
}

void Player::moveLeft()
{
	body.setVelocity({ -PLAYER_MOVE_POWER, body.getVelocity().y });
}

void Player::moveRight()
{
	body.setVelocity({ PLAYER_MOVE_POWER, body.getVelocity().y });
}

void Player::jump(double power)
{
	power = Clamp(power, 0.0, 1.0);

	body.setVelocity({ body.getVelocity().x, -PLAYER_JUMP_POWER * power });
}

void Player::descendScaffold()
{
	P2Filter filter = body.shape(0).getFilter();

	if (!(filter.maskBits & CollisionCategory::Scaffold)) return;

	body.shape(0).setFilter({
		filter.categoryBits,
		static_cast<uint16>(filter.maskBits & ~CollisionCategory::Scaffold)
	});

	SetTimeout([this, filter] { body.shape(0).setFilter(filter); }, 500ms);
}

void Player::shoot()
{
	Vec2 pos = body.getPos() + aim * 100;

	Stage::GetInstance()->createObject<Bullet>(pos, aim);
}
