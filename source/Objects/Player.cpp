# include "Player.hpp"
# include "../Stages/Stage.hpp"
# include "Box1.hpp"

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position)
{
	body = world.createRect(P2Dynamic, position, SizeF{ 100, 100 });

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

	if (KeyEnter.pressed()) Stage::GetInstance()->createObject<Box1>(Vec2{ (Scene::Width() / 2), 0 });

	if (KeyH.down()) heal(10);

	if (body.getPos().y >= 1000) die();
}

void Player::draw() const
{
	TextureAsset(U"Player").mirrored(body.getVelocity().x > 0.0).resized(SizeF{ 100, 100 }).drawAt(body.getPos());

	body.drawFrame();
}
