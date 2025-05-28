# include "Base.hpp"
# include "../Stages/Stage.hpp"

void ObjectBase::deleteSelf()
{
	Stage::GetInstance()->deleteObject(this);
}
