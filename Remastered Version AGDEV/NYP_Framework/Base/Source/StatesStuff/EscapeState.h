#pragma once

#ifndef ESCAPE_ID_
#define ESCAPE_ID_ 1
#endif

#include "StateComponent.h"

class EscapeState : public StateComponent
{
public:
    EscapeState();
    virtual ~EscapeState();

    virtual void Update(double dt);

    virtual bool onNotify(const float &zeEvent);
    virtual bool onNotify(EntityBase &zeEvent);

protected:
    EntityBase *thePlayer;
};