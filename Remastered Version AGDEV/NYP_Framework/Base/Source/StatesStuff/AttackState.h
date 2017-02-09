#pragma once

#ifndef ATTACK_ID_
#define ATTACK_ID_ 1
#endif

#include "StateComponent.h"

class AttackState : public StateComponent
{
public:
    AttackState();
    virtual ~AttackState();

    virtual void Update(double dt);

    virtual bool onNotify(const float &zeEvent);
    virtual bool onNotify(EntityBase &zeEvent);

protected:
    EntityBase *thePlayer;
	Vector3 vel;

	float attackCooldown;
};