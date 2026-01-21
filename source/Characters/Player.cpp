# include "Player.hpp"
# include "Enemies/Enemy1.hpp"
# include "Enemies/Enemy2.hpp"
# include "../Stages/Stage.hpp"
# include "../Objects/Boxes/Box1.hpp"
# include "../Objects/Boxes/Box2.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Objects/Bullet.hpp"
# include "../Objects/Scaffold.hpp"
# include "../Utils/TimerUtils.hpp"

using namespace TimerUtils;

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position), start_position(position), pass_through_category(CollisionCategory::None), aim(Vec2{ 1, 0 }), damaged(false), descend_scaffold(false), mirrored(false)
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

	if (current_position.y >= (Scene::Height() + 100)) die();

	if (pass_through_category != CollisionCategory::None)
	{
		if (pass_through_area == Rect{ 0 })
		{
			pass_through_category = CollisionCategory::None;
		}
		else
		{
			if (auto pp = body.as<P2Polygon>(0))
			{
				Polygon p = pp->getPolygon();

				if (!p.intersects(pass_through_area))
				{
					body.shape(0).setFilter(filter);

					pass_through_category = CollisionCategory::None;
					pass_through_area     = Rect{ 0 };

					descend_scaffold = false;
				}
			}
		}
	}

	handleInput();
}

void Player::draw() const
{
	Line(current_position, current_position + aim * 100).draw();

	if (not InRange(body.getVelocity().x, -1.0, 1.0)) mirrored = body.getVelocity().x > 0.0;

	TextureAsset(U"Player").mirrored(mirrored).resized({ 105, 105 }).rotated(body.getAngle()).drawAt(current_position, damaged ? ColorF{ 1.0, 0.25, 0.25, 0.5 } : ColorF{ 1.0 });

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void Player::onHit(ObjectBase& object, const P2Collision& collision)
{
	if (Enemy1* enemy1 = dynamic_cast<Enemy1*>(&object))
	{
		if (Abs((current_position.y + 50) - collision.contact(0).point.y) < 10.0) enemy1->applyDamage(Random(70.0f, 90.0f));
	}

	if (pass_through_category != CollisionCategory::None && pass_through_area == Rect{ 0 })
	{
		if (object.getBody().shape(0).getShapeType() != P2ShapeType::Rect) return;

		if (descend_scaffold)
		{
			if (Scaffold* scaffold = dynamic_cast<Scaffold*>(&object))
			{
				if (!scaffold->canPassThrough()) return;
			}
		}

		if (object.getBody().num_shapes() < 2) return;

		if (auto pr = object.getBody().as<P2Rect>(1))
		{
			Quad q = pr->getQuad();

			pass_through_area = q.boundingRect().asRect();

			filter = body.shape(0).getFilter();

			if (!(filter.maskBits & pass_through_category)) return;

			body.shape(0).setFilter({
				filter.categoryBits,
				static_cast<uint16>(filter.maskBits & ~pass_through_category)
			});
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

		aim = (cursorPos - current_position).normalized();
	}

	jump(d);

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

void Player::jump(Duration duration)
{
	if (duration <= 0ms) return;

	if (duration >= PLAYER_MAX_JUMP_HOLD) return;

	body.setVelocity({ body.getVelocity().x, -(PLAYER_JUMP_POWER * (duration >= (PLAYER_MAX_JUMP_HOLD * 0.75) ? 1.25 : 1)) });
}

void Player::shoot()
{
	Vec2 pos = current_position + aim * 100;

	Stage::GetInstance()->createObject<Bullet>(pos, aim);
}
