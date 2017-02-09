#include "HealState.h"
#include "../PlayerInfo/PlayerInfo.h"

HealState::HealState()
{
    name_ = "HEALING";
    Own_ID_ = HEAL_ID_;
    thePlayer = nullptr;
    owner_ = nullptr;
    influenceRadius = 4;
	timer = 0.f;
	//isHitByPlayer = false;
}

HealState::~HealState()
{

}

void HealState::Update(double dt)
{
	timer += dt;
	haveBullet = false;
	if (timer > 0.5f)
	{
		timer = 0.f;
		int hp = owner_->getHealth() + 1;
		owner_->setHealth(hp);
	}
	if (owner_->getHealth() == 100)
	{
		FSM_->switchState(0);
		//owner_->SetRotation2(0);
	}
	findClosestBullet();

	if (!haveBullet)
	{
		if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() < 3000)
		{
			FSM_->switchState(2);
			owner_->setFindClosestPoint(true);
		}
	}
	else
	{
		if (((*closestBullet)->GetPosition() - owner_->GetPosition()).LengthSquared() < (zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared())
		{//ifbullet is closer to ship
			if (((*closestBullet)->GetPosition() - owner_->GetPosition()).LengthSquared() < 3000)
			{
				FSM_->switchState(2);
				owner_->setFindClosestPoint(true);
			}
		}
		else
		{//if player is closer
			if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() < 3000)
			{
				FSM_->switchState(2);
				owner_->setFindClosestPoint(true);
			}
		}
	}
}

bool HealState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    return false;
}

bool HealState::onNotify(EntityBase &zeEvent)
{
    return false;
}

void HealState::findClosestBullet()
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