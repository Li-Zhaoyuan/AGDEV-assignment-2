#include "EscapeState.h"
#include "../PlayerInfo/PlayerInfo.h"

EscapeState::EscapeState()
{
    name_ = "ESCAPING";
    Own_ID_ = ESCAPE_ID_;
    thePlayer = nullptr;
    owner_ = nullptr;
    influenceRadius = 4;
	//isHitByPlayer = false;
}

EscapeState::~EscapeState()
{

}

void EscapeState::Update(double dt)
{
	Vector3 vel;
	haveBullet = false;
	//(*closestBullet) = nullptr;

	findClosestBullet();

	if (!haveBullet)
	{
		if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() < 5000)
		{
			vel = -(zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).Normalized();
			vel *= 50;
		}
		if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() > 5000)
		{
			vel.SetZero();
			FSM_->switchState(3);
		}
	}
	else
	{
		if (((*closestBullet)->GetPosition() - owner_->GetPosition()).LengthSquared() < (zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared())
		{//ifbullet is closer to ship
			if (((*closestBullet)->GetPosition() - owner_->GetPosition()).LengthSquared() < 5000)
			{
				vel = -((*closestBullet)->GetPosition() - owner_->GetPosition()).Normalized();
				vel *= 50;
			}
			if (((*closestBullet)->GetPosition() - owner_->GetPosition()).LengthSquared() > 5000)
			{
				vel.SetZero();
				FSM_->switchState(3);
			}
		}
		else
		{//if player is closer
			if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() < 5000)
			{
				vel = -(zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).Normalized();
				vel *= 50;
			}
			if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() > 5000)
			{
				vel.SetZero();
				FSM_->switchState(3);
			}
		}
	}
	//for (std::vector<GenericEntity*>::iterator it = (*m_activeList).begin(); it != (*m_activeList).end(); ++it)
	//{
	//	if ((*it)->getName().find("Projectile") != std::string::npos)//find bullet
	//	{
	//		if (((*it)->GetPosition() - owner_->GetPosition()).LengthSquared() <= 300)
	//		{
	//			vel = -((*it)->GetPosition() - owner_->GetPosition()).Normalized();
	//			vel *= 50;
	//		}
	//	}
	//}

	Vector3 temp = owner_->GetPosition();
	temp += vel * dt;
	if (!vel.IsZero())
		owner_->SetRotation(Math::RadianToDegree(atan2(vel.x, vel.z)));
	owner_->SetPosition(temp);
}

bool EscapeState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    return false;
}

bool EscapeState::onNotify(EntityBase &zeEvent)
{
    return false;
}

void EscapeState::findClosestBullet()
{
	float closest;
	bool toggle = false;
	for (std::vector<GenericEntity*>::iterator it = (*m_activeList).begin(); it != (*m_activeList).end(); ++it)
	{
		if ((*it)->getName().find("Projectile") != std::string::npos)//find bullet
		{
			closest = ((*it)->GetPosition() - owner_->GetPosition()).LengthSquared();
			closestBullet = it;
			toggle = true;
		}

	}
	if (!toggle)
	{
		haveBullet = false;
		return;
	}
	else
	{
		haveBullet = true;
	}
	for (std::vector<GenericEntity*>::iterator it = (*m_activeList).begin(); it != (*m_activeList).end(); ++it)
	{
		if (((*it)->GetPosition() - owner_->GetPosition()).LengthSquared() < closest && (*it)->getName().find("Projectile") != std::string::npos)
		{
			closest = ((*it)->GetPosition() - owner_->GetPosition()).LengthSquared();
			closestBullet = it;
		}

	}

	
}