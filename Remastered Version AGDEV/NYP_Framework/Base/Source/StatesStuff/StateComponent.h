#pragma once

#include "StateMachineComponent.h"
#include "GenericComponent.h"

class StateMachineComponent;

class StateComponent : public GenericComponent
{
    friend class StateMachineComponent;
public:
    virtual ~StateComponent() { FSM_ = nullptr; changedName = false; originalOwnerName = ""; influenceRadius = 0; Own_ID_ = 0; };

    void setFSM(StateMachineComponent &zeFSM) { FSM_ = &zeFSM; }


protected:
    unsigned char Own_ID_;
    StateMachineComponent *FSM_;
    StateComponent() { FSM_ = nullptr; };
    std::string originalOwnerName;
    bool changedName;
    float influenceRadius;
};

