#include "AttackState.h"

AttackState::AttackState()
{
    name_ = "ATTACKING";
    Own_ID_ = ATTACK_ID_;
    thePlayer = nullptr;
    owner_ = nullptr;
    influenceRadius = 4;
}

AttackState::~AttackState()
{

}

void AttackState::Update(double dt)
{

}

bool AttackState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    return false;
}

bool AttackState::onNotify(EntityBase &zeEvent)
{
    return false;
}