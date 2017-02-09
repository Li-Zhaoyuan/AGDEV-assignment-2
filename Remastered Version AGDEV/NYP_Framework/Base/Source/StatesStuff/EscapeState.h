#pragma once

#ifndef ESCAPE_ID_
#define ESCAPE_ID_ 2
#endif

#include "StateComponent.h"
class GenericEntity;
class EscapeState : public StateComponent
{
public:
    EscapeState();
    virtual ~EscapeState();

    virtual void Update(double dt);

    virtual bool onNotify(const float &zeEvent);
    virtual bool onNotify(EntityBase &zeEvent);

	void findClosestBullet();

protected:
    EntityBase *thePlayer;
	bool haveBullet;
	std::vector<GenericEntity*>::iterator closestBullet;
};