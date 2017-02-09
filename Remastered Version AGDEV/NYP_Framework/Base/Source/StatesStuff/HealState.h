#pragma once

#ifndef HEAL_ID_
#define HEAL_ID_ 3
#endif

#include "StateComponent.h"

class HealState : public StateComponent
{
public:
    HealState();
    virtual ~HealState();

    virtual void Update(double dt);

    virtual bool onNotify(const float &zeEvent);
    virtual bool onNotify(EntityBase &zeEvent);

	void findClosestBullet();

protected:
    EntityBase *thePlayer;
	float timer;
	bool haveBullet;
	std::vector<GenericEntity*>::iterator closestBullet;
};