# include "Player.hpp"
# include "../Stages/Stage.hpp"
# include "./Box1.hpp"

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position)
{
	body = world.createRect(P2Dynamic, position, SizeF{ 100, 100 });

	body.setFixedRotation(true);

	hp = 100;

	this->initialize();
}

Player::~Player()
{
	this->finalize();
}

void Player::initialize()
{

}

void Player::update()
{
	if (KeyA.pressed())  body.applyLinearImpulse(Vec2{ -10,    0 });
	if (KeyD.pressed())  body.applyLinearImpulse(Vec2{  10,    0 });
	if (KeySpace.down()) body.applyLinearImpulse(Vec2{   0, -500 });

	if (KeyEnter.pressed())
	{
		Stage::GetInstance()->createObject<Box1>(Vec2{ (Scene::Width() / 2), 0 });
	}

	if (body.getPos().y >= 1000 || hp <= 0)
	{
		Stage::GetInstance()->deleteObject(this);
	}
}

void Player::draw() const
{
	TextureAsset(U"Player").mirrored(body.getVelocity().x > 0.0).resized(SizeF{ 100, 100 }).drawAt(body.getPos());
	
	body.drawFrame();
}

void Player::finalize()
{

}
