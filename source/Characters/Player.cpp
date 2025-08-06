# include "Player.hpp"
# include "../Stages/Stage.hpp"
# include "../Objects/Boxes/Box1.hpp"
# include "../Objects/Boxes/Box2.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Characters/Enemies/Enemy1.hpp"
# include "../Characters/Enemies/Enemy2.hpp"

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position)
{
	body = world.createPolygon(
		P2Dynamic,
		position,
		Polygon{
			{
				Vec2{ -10,  50 },
				Vec2{ -30,  30 },
				Vec2{ -30, -30 },
				Vec2{ -10, -50 },
				Vec2{  10, -50 },
				Vec2{  30, -30 },
				Vec2{  30,  30 },
				Vec2{  10,  50 }
			}
		},
		P2Material{
			.friction = 0.5
		},
		P2Filter{
			.categoryBits = CollisionCategory::Player,
			.maskBits     = CollisionCategory::All
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
	handleInput();

	if (body.getPos().y >= (Scene::Height() + 100)) die();
}

void Player::draw() const
{
	static bool mirrored = false;

	if (not InRange(body.getVelocity().x, -1.0, 1.0)) mirrored = body.getVelocity().x > 0.0;

	TextureAsset(U"Player").mirrored(mirrored).resized({ 105, 105 }).rotated(body.getAngle()).drawAt(body.getPos());

#ifdef _DEBUG
	body.drawFrame();
#endif
}

void Player::handleInput()
{
	if (KeyA.pressed()) moveLeft();
	if (KeyD.pressed()) moveRight();

	if (KeySpace.down() || KeyW.down()) jump();

	size_t playerIndex = 0;

	auto controller = XInput(playerIndex);

	if (controller.isConnected())
	{
		const double stickDeadZone = 0.2;

		if (controller.buttonLeft .pressed() || controller.leftThumbX < -stickDeadZone) moveLeft();
		if (controller.buttonRight.pressed() || controller.leftThumbX >  stickDeadZone) moveRight();

		if (controller.buttonA.down() || controller.buttonUp.down() || controller.leftThumbY > stickDeadZone) jump();
	}

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

void Player::jump()
{
	body.setVelocity({ body.getVelocity().x, -PLAYER_JUMP_POWER });
}
