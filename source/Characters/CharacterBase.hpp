# pragma once

# include "../Objects/ObjectBase.hpp"

class CharacterBase : public ObjectBase
{
public:
	CharacterBase(P2World& world, const Vec2& position) : ObjectBase(world, position) {}
	virtual ~CharacterBase() = default;

	float getHP   () const { return hp; }
	float getMaxHP() const { return max_hp; }

	virtual void applyDamage(float amount) { onDamaged(amount); }
	virtual void heal       (float amount) { onHealed (amount); }

	virtual void kill() { applyDamage(max_hp); }

protected:
	float hp, max_hp;

	void addHP(float amount) { hp += amount; hp = std::clamp(hp, 0.0f, max_hp); }

	virtual void die() { destroy(); }

	virtual void onDamaged(float amount) { addHP(-amount); if (!hp) die(); }
	virtual void onHealed (float amount) { addHP( amount); }
};
