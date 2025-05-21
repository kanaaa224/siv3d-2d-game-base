# include "Player.hpp"

# include "../Stages/Stage1.hpp"
# include "./Box1.hpp"

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position)
{
	body = world.createRect(P2Dynamic, position, SizeF{ 100, 100 });

	body.setFixedRotation(true);

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
	if (KeyA.pressed()) body.applyLinearImpulse(Vec2{ -10, 0 });
	if (KeyD.pressed()) body.applyLinearImpulse(Vec2{  10, 0 });

	if (KeySpace.down()) body.applyLinearImpulse(Vec2{ 0, -500 });

	if (KeyEnter.down())
	{
		Stage* stage = Stage::GetInstance();

		stage->createObject<Box1>(Vec2{ 640, 100 });
	}

	if (body.getPos().y >= 1000) {
		body.setPos(Vec2{ 320, 500 });
		body.setVelocity(Vec2{});
	}
}

void Player::draw() const
{
	TextureAsset(U"Player").mirrored(body.getVelocity().x > 0.0).resized(SizeF{ 100, 100 }).drawAt(body.getPos());
	
	body.drawFrame();
}

void Player::onHit(ObjectBase& object)
{
	CharacterBase* character = dynamic_cast<CharacterBase*>(&object);

	if (character) object.getBody().applyLinearImpulse(Vec2{ 0, -10 });
}

void Player::finalize()
{

}
