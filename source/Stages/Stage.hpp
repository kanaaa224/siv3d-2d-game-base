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
	void deleteObject(ObjectBase* object) { if (object && not objects_deletion.contains(object)) objects_deletion << object; }

	static void DeleteInstance();
	static void NewInstance();
	static Stage* GetInstance();

	void setSceneFunctions(
		const std::function<bool(SceneState, Duration)>& changeSceneFunc,
		const std::function<SceneData&()>& getDataFunc
	) {
		sceneChange = changeSceneFunc;
		sceneData   = getDataFunc;
	}

	std::function<bool(SceneState, Duration)> sceneChange;
	std::function<SceneData&()>               sceneData;

protected:
	Array<ObjectBase*> objects;
	Array<ObjectBase*> objects_deletion;

	P2World world;

	const double step_time;

	double accumulated_time;

	static Stage* instance;
};
