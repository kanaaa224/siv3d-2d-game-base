# pragma once

# include "../Objects/ObjectBase.hpp"

class Stage
{
public:
	Stage();
	virtual ~Stage() = default;

	virtual void update();
	virtual void draw() const;

	static Stage* GetInstance();

	template <class T, class... Args>
	bool createObject(Args&&... args) { static_assert(std::is_base_of<ObjectBase, T>::value); objects << new T(world, std::forward<Args>(args)...); return true; }

protected:
	Array<ObjectBase*> objects;

	P2World world;

	const double stepTime;

	double accumulatedTime;

private:
	static Stage* instance;
};
