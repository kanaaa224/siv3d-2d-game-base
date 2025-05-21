# pragma once

# include "../Objects/ObjectBase.hpp"

class Stage
{
public:
	Stage();
	virtual ~Stage();

	virtual void update();
	virtual void draw() const;

	template <class T, class... Args>
	void createObject(Args&&... args) { static_assert(std::is_base_of<ObjectBase, T>::value); objects << new T(world, std::forward<Args>(args)...); }
	void deleteObject(ObjectBase* object) { if (object && !deletionObjects.contains(object)) deletionObjects << object; }

	static void   NewInstance();
	static Stage* GetInstance();

protected:
	Array<ObjectBase*> objects;
	Array<ObjectBase*> deletionObjects;

	P2World world;

	const double stepTime;

	double accumulatedTime;

	static Stage* instance;
};
