#include "AttackState.h"
#include "../PlayerInfo/PlayerInfo.h"

AttackState::AttackState()
{
    name_ = "ATTACKING";
    Own_ID_ = ATTACK_ID_;
    thePlayer = nullptr;
    owner_ = nullptr;
    influenceRadius = 4;
	vel.SetZero();
}

AttackState::~AttackState()
{

}

void AttackState::Update(double dt)
{
	if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() >= 100)
	{
		vel.SetZero();
		FSM_->switchState(0);
	}

	Vector3 temp = owner_->GetPosition();
	temp += vel * dt;
	//float temp777 = Math::RadianToDegree(atan2(vel.z, vel.x));
	if (!vel.IsZero())
		owner_->SetRotation(Math::RadianToDegree(atan2(vel.x, vel.z)));
	owner_->SetPosition(temp);
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