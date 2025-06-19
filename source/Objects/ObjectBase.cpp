# include "ObjectBase.hpp"
# include "../Stage.hpp"

void ObjectBase::deleteSelf()
{
	Stage::GetInstance()->deleteObject(this);
}
