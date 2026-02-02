# pragma once

# include "../Objects/ObjectBase.hpp"

# define DEFAULT_HP 100

class CharacterBase : public ObjectBase
{
public:
	CharacterBase(P2World& world, const Vec2& position) : ObjectBase(world, position), max_hp(DEFAULT_HP), hp(max_hp) {}

	int32 getMaxHP() const { return max_hp; }
	int32 getHP   () const { return hp; }

	virtual void applyDamage(int32 amount) { onDamaged(amount); }
	virtual void heal       (int32 amount) { onHealed (amount); }

	virtual void kill() { applyDamage(max_hp); }

protected:
	int32 max_hp, hp;

	virtual void addHP(int32 amount) { hp += amount; hp = std::clamp(hp, 0, max_hp); }

	virtual void die() { destroy(); }

	virtual void onDamaged(int32 amount) { addHP(-amount); if (!hp) die(); }
	virtual void onHealed (int32 amount) { addHP( amount); }
};
