# include "Player.hpp"
# include "../Stages/Stage.hpp"
# include "../Objects/Boxes/Box1.hpp"
# include "../Objects/Boxes/Box2.hpp"
# include "../Objects/Punipuni.hpp"
# include "../Characters/Enemies/Enemy1.hpp"
# include "../Characters/Enemies/Enemy2.hpp"

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position)
{
	body = world.createRect(
		P2Dynamic,
		position,
		SizeF { 100, 100 },
		P2Material {},
		P2Filter {
			.categoryBits = CollisionCategory::Player,
			.maskBits     = CollisionCategory::All & ~CollisionCategory::Box2
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
	if (KeyA.pressed())  body.applyLinearImpulse({ -10,    0 });
	if (KeySpace.down()) body.applyLinearImpulse({   0, -500 });
	if (KeyD.pressed())  body.applyLinearImpulse({  10,    0 });

	if (Key1.pressed()) Stage::GetInstance()->createObject<Box1>    (Vec2{ (Scene::Width() / 2), 0 });
	if (Key2.pressed()) Stage::GetInstance()->createObject<Box2>    (Vec2{ (Scene::Width() / 2), 0 });
	if (Key3.pressed()) Stage::GetInstance()->createObject<Punipuni>(Vec2{ (Scene::Width() / 2), 0 });
	if (Key4.pressed()) Stage::GetInstance()->createObject<Enemy1>  (Vec2{ (Scene::Width() / 2), 0 });
	if (Key5.pressed()) Stage::GetInstance()->createObject<Enemy2>  (Vec2{ (Scene::Width() / 2), 0 });

	if (KeyQ.down()) Stage::GetInstance()->sceneChange(SceneState::Title, 0.5s);

	if (KeyH.down()) heal(10);

	if (body.getPos().y >= (Scene::Height() + 100)) die();
}

void Player::draw() const
{
	static bool mirrored = false;

	if (not InRange(body.getVelocity().x, -1.0, 1.0)) mirrored = body.getVelocity().x > 0.0;

	TextureAsset(U"Player").mirrored(mirrored).resized({ 100, 100 }).drawAt(body.getPos());

	body.drawFrame();
}
