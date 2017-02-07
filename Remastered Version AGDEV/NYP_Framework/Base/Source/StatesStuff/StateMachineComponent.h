#pragma once

#include "StateComponent.h"
#include "GenericComponent.h"
#include <vector>

class StateComponent;

class StateMachineComponent : public GenericComponent
{
public:
    StateMachineComponent();
    virtual ~StateMachineComponent();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    void addStates(StateComponent &zeStates);
    void switchState(const size_t &zeID);
    void switchState(const std::string &zeName);
    bool transitToPreviousState();


    StateComponent &getSpecificStates(const size_t &zeNum);
    StateComponent &getSpecificStates(const std::string &zeName);
    StateComponent &getCurrentState();

	virtual bool onNotify(GenericComponent &zeEvent);

protected:
    std::vector<StateComponent*> allRegisteredStates, HistoryOfStates;
};
