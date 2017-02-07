#include "GenericComponent.h"


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