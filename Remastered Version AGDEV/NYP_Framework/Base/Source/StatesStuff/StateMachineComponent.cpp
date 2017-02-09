#include "StateMachineComponent.h"



StateMachineComponent::StateMachineComponent()
{
    Init();
}

StateMachineComponent::~StateMachineComponent()
{
    for (auto it : allRegisteredStates)
        if (it)
            delete it;
    allRegisteredStates.clear();
    HistoryOfStates.clear();
}

void StateMachineComponent::Init()
{
    allRegisteredStates.resize(2, nullptr);
}

void StateMachineComponent::Update(double dt)
{
    //if (!HistoryOfStates.empty())
        HistoryOfStates.back()->Update(dt);
}

void StateMachineComponent::Exit()
{
    HistoryOfStates.clear();
    for (std::vector<StateComponent*>::iterator it = allRegisteredStates.begin(), end = allRegisteredStates.end(); it != end; ++it)
    {
        if (*it)
            (*it)->Exit();
    }
    HistoryOfStates.push_back(allRegisteredStates[0]);
}

void StateMachineComponent::addStates(StateComponent &zeStates)
{
    while (allRegisteredStates.size() <= zeStates.Own_ID_)
    {
        allRegisteredStates.resize(allRegisteredStates.size() * 2, nullptr);
    }
    if (!allRegisteredStates[zeStates.Own_ID_])
    {
        allRegisteredStates[zeStates.Own_ID_] = &zeStates;
        if (HistoryOfStates.empty())
            HistoryOfStates.push_back(&zeStates);
        zeStates.setEntityOwner(owner_);
		zeStates.setPlayer(zePlayer);
        zeStates.setFSM(*this);
    }
}

bool StateMachineComponent::transitToPreviousState()
{
    if (HistoryOfStates.size() > 1) {
        HistoryOfStates.back()->Exit();
        HistoryOfStates.pop_back();
        return true;
    }
    return false;
}

void StateMachineComponent::switchState(const size_t &zeID)
{
    HistoryOfStates.back()->Exit();
    HistoryOfStates.push_back(allRegisteredStates[zeID]);
}

void StateMachineComponent::switchState(const std::string &zeName)
{
    for (std::vector<StateComponent*>::iterator it = allRegisteredStates.begin(), end = allRegisteredStates.end(); it != end; ++it)
    {
        if ((*it)->getName() == zeName)
        {
            HistoryOfStates.back()->Exit();
            HistoryOfStates.push_back(*it);
            break;
        }
    }
}

StateComponent &StateMachineComponent::getSpecificStates(const size_t &zeNum)
{
    return *allRegisteredStates[zeNum];
}

StateComponent &StateMachineComponent::getSpecificStates(const std::string &zeName)
{
    std::vector<StateComponent*>::iterator it = allRegisteredStates.begin();
    for (std::vector<StateComponent*>::iterator it = allRegisteredStates.begin(), end = allRegisteredStates.end(); it != end; ++it)
    {
        if ((*it)->getName() == zeName)
        {
            break;
        }
    }
    return **it;
}

StateComponent &StateMachineComponent::getCurrentState()
{
    return *HistoryOfStates.back();
}

bool StateMachineComponent::onNotify(GenericComponent &zeEvent)
{
	return HistoryOfStates.back()->onNotify(zeEvent);
}