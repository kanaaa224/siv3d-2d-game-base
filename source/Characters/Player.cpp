# include "Player.hpp"
# include "../Stage.hpp"
# include "../Objects/Boxes/1.hpp"
# include "../Objects/Boxes/2.hpp"

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position), mirrored(false)
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
	max_hp = 100;

	hp = max_hp;
}

void Player::update()
{
	if (KeyA.pressed())  body.applyLinearImpulse(Vec2{ -10,    0 });
	if (KeySpace.down()) body.applyLinearImpulse(Vec2{   0, -500 });
	if (KeyD.pressed())  body.applyLinearImpulse(Vec2{  10,    0 });

	if (Key1.pressed()) Stage::GetInstance()->createObject<Box1>(Vec2{ (Scene::Width() / 2), 0 });
	if (Key2.pressed()) Stage::GetInstance()->createObject<Box2>(Vec2{ (Scene::Width() / 2), 0 });

	if (KeyH.down()) heal(10);

	if (body.getPos().y >= 1000) die();
	
	if (not InRange(body.getVelocity().x, -1.0, 1.0)) mirrored = body.getVelocity().x > 0.0;
}

void Player::draw() const
{
	TextureAsset(U"Player").mirrored(mirrored).resized(SizeF{ 100, 100 }).drawAt(body.getPos());

	body.drawFrame();
}
