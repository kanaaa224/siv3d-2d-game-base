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

	static void DeleteInstance();
	static void NewInstance();
	static Stage* GetInstance();

	void setSceneFunctions(
		const std::function<void(SceneState, Duration)>& changeSceneFunc,
		const std::function<SceneData&()>& getDataFunc
	) {
		sceneChange = changeSceneFunc;
		sceneData   = getDataFunc;
	}

	std::function<void(SceneState, Duration)> sceneChange;
	std::function<SceneData&()> sceneData;

protected:
	Array<ObjectBase*> objects;
	Array<ObjectBase*> deletionObjects;

	P2World world;

	const double stepTime;

	double accumulatedTime;

	static Stage* instance;
};
