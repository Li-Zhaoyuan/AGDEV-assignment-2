#include "GenericComponent.h"
#include "../GenericEntity.h"


GenericComponent::GenericComponent()
{
    GenericComponent("", nullptr);
}

GenericComponent::GenericComponent(const std::string &zeName)
{
    GenericComponent(zeName, nullptr);
}

GenericComponent::GenericComponent(const std::string &zeName, EntityBase *zeOwner)
{
    setName(zeName);
}

GenericComponent::~GenericComponent()
{
    Exit();
}

void GenericComponent::setName(const std::string zeName) 
{ 
    name_ = zeName; 
}

std::string GenericComponent::getName()
{
    return name_;
}

void GenericComponent::Init()
{

}

void GenericComponent::Update(double dt)
{

}

void GenericComponent::Exit()
{
    owner_ = nullptr;
}

void GenericComponent::setEntityOwner(EntityBase *zeOwner)
{
    owner_ = zeOwner;
}

EntityBase *GenericComponent::getOwner()
{
    return owner_;
}

void GenericComponent::setPlayer(CPlayerInfo *player)
{
	zePlayer = player;
}

CPlayerInfo *GenericComponent::getPlayer()
{
	return zePlayer;
}
void GenericComponent::setVectorOfBullets(std::vector<GenericEntity*> *m_activeList)
{
	this->m_activeList = m_activeList;
}
std::vector<GenericEntity*> GenericComponent::getVectorOfBullets()
{
	return *m_activeList;
}
//void GenericComponent::setIsHitByPlayer(bool toggle)
//{
//	isHitByPlayer = toggle;
//}
//bool GenericComponent::getIsHitByPlayer()
//{
//	return isHitByPlayer;
//}