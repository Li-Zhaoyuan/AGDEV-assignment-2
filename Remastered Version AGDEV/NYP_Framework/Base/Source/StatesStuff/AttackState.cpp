#include "AttackState.h"
#include "../PlayerInfo/PlayerInfo.h"

AttackState::AttackState()
{
    name_ = "ATTACKING";
    Own_ID_ = ATTACK_ID_;
    thePlayer = nullptr;
    owner_ = nullptr;
    influenceRadius = 4;
	attackCooldown = 0.f;
	vel.SetZero();
	//isHitByPlayer = false;
}

AttackState::~AttackState()
{

}

void AttackState::Update(double dt)
{
	attackCooldown += dt;
	if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() >= 2000 && !owner_->getisHhitByPlayer())
	{
		vel.SetZero();
		FSM_->switchState(0);
		owner_->SetRotation2(0);
		owner_->setFindClosestPoint(true);
		
	}
	if (owner_->getHealth() < 50)
	{
		vel.SetZero();
		owner_->SetRotation2(0);
		FSM_->switchState(2);
		owner_->setIsHitByPlayer(false);
	}

	if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() >= 100 || owner_->getisHhitByPlayer())
	{
		vel = (zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).Normalized();
		vel *= 20;
	}
	if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() < 100 && attackCooldown > 2.f)
	{
		owner_->setIsHitByPlayer(false);
		int hp = zePlayer->thePlayerEntity.getHealth();
		zePlayer->thePlayerEntity.setHealth(hp - 10);
		attackCooldown = 0.f;
	}
	Vector3 temp = owner_->GetPosition();
	temp += vel * dt;
	//float temp777 = Math::RadianToDegree(atan2(vel.z, vel.x));

	float attackRotation;
	attackRotation = owner_->GetRotation2();
	attackRotation += 1000 * dt;
	owner_->SetRotation2(attackRotation);
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