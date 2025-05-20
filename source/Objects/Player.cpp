# include "Player.hpp"

Player::Player(P2World& world, const Vec2& position) : CharacterBase(world, position)
{
	body = world.createRect(P2Dynamic, position, SizeF{ 100, 100 });

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
}

void Player::draw() const
{
	TextureAsset(U"Player").mirrored(body.getVelocity().x > 0.0).resized(SizeF{ 100, 100 }).drawAt(body.getPos());
	
	body.drawFrame();
}

void Player::onHit(ObjectBase& object)
{
	(void)object;
}

void Player::onHit(CharacterBase& object)
{
	(void)object;
}

void Player::finalize()
{

}
