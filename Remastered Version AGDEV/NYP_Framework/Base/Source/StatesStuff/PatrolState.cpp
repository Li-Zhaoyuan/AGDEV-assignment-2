#include "PatrolState.h"
#include "../../lua/LuaInterface.h"
#include "../PlayerInfo/PlayerInfo.h"

#define speed 30

PatrolState::PatrolState()
{
    name_ = "PATROL";
    owner_ = nullptr;
    Own_ID_ = PATROL_ID_;
    //WayPointsInMap = nullptr;
    IndexOfWaypoint = 0;
    thePlayer_ = nullptr;
    influenceRadius = 4;
    wayPtInfluenceSq = 4;
	vel.SetZero();
	isAtWayPoint = false;
	initWayPoints();
	//isHitByPlayer = false;
}

PatrolState::~PatrolState()
{
    Exit();
}

void PatrolState::Update(double dt)
{
    if (owner_)
    {
        //owner_ 
    }
	if (owner_->getFindClosestPoint())
	{
		setClosestWaypointtoGo();
		owner_->setFindClosestPoint(false);
	}
	if (owner_->getHealth() < 50)
	{
		vel.SetZero();
		isAtWayPoint = false;
		FSM_->switchState(2);
		owner_->setFindClosestPoint(true);
	}
	if (!isAtWayPoint)
	{
		if ((owner_->GetPosition() - (*waypointIT)).LengthSquared() < 50)
		{
			isAtWayPoint = true;
		}
		else
		{
			Vector3 temp;
			//temp = -(owner_->GetPosition() - (*waypointIT));
			temp = (*waypointIT) - owner_->GetPosition();
			temp.Normalize();
			temp *= speed;
			vel.Set(temp.x, temp.y, temp.z);
		}
	}
	if (isAtWayPoint)
	{
		if (waypointIT != WayPointsInMap.end() - 1)
		{
			++waypointIT;
			isAtWayPoint = false;
		}
		else
		{
			waypointIT = WayPointsInMap.begin();
			isAtWayPoint = false;
		}
	}
	
	if ((zePlayer->thePlayerEntity.GetPosition() - owner_->GetPosition()).LengthSquared() <= 1000 || owner_->getisHhitByPlayer())
	{
		vel.SetZero();
		FSM_->switchState(1);
		owner_->setFindClosestPoint(true);
	}

	for (std::vector<GenericEntity*>::iterator it = (*m_activeList).begin(); it != (*m_activeList).end(); ++it)
	{
		if ((*it)->getName().find("Projectile") != std::string::npos)//find bullet
		{
			if (((*it)->GetPosition() - owner_->GetPosition()).LengthSquared() <= 100)
			{
				vel.SetZero();
				FSM_->switchState(1);
				owner_->setIsHitByPlayer(true);
			}
		}
	}
	//std::vector<GenericEntity*> y = *m_activeList;

	Vector3 temp = owner_->GetPosition();
	temp += vel * dt;
	//float temp777 = Math::RadianToDegree(atan2(vel.z, vel.x));
	if (!vel.IsZero())
		owner_->SetRotation(Math::RadianToDegree(atan2(vel.x, vel.z)));
	owner_->SetPosition(temp);
}

void PatrolState::initWayPoints()
{
	LuaInterface::GetInstance()->theWayPointState = lua_open();
	luaL_openlibs(LuaInterface::GetInstance()->theWayPointState);
	luaL_dofile(LuaInterface::GetInstance()->theWayPointState, "lua/waypointpos.lua");
	
	int i = 0;
	while (i < 3)
	{
		std::string str = "satelite";
		str.append(std::to_string((i + 1)));
		lua_getglobal(LuaInterface::GetInstance()->theWayPointState, str.c_str());

		Vector3 waypoint(LuaInterface::GetInstance()->getField(LuaInterface::GetInstance()->theWayPointState, "x"), LuaInterface::GetInstance()->getField(LuaInterface::GetInstance()->theWayPointState, "y"), LuaInterface::GetInstance()->getField(LuaInterface::GetInstance()->theWayPointState,"z"));
		WayPointsInMap.push_back(waypoint);
		++i;
	}

	lua_close(LuaInterface::GetInstance()->theWayPointState);
	waypointIT = WayPointsInMap.begin();
}

void PatrolState::Exit()
{

}

bool PatrolState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        wayPtInfluenceSq = zeEvent;
        return true;
    }
    else if (zeEvent < -Math::EPSILON)
    {
        influenceRadius = -zeEvent;
        return true;
    }
    return false;
}

bool PatrolState::onNotify(EntityBase &zeEvent)
{
    return false;
}

void PatrolState::setClosestWaypointtoGo()
{
	float closest;
	for (std::vector<Vector3>::iterator it = WayPointsInMap.begin(); it != (WayPointsInMap).end(); ++it)
	{
		if (it == WayPointsInMap.begin())
		{
			closest = ((*it)- owner_->GetPosition()).LengthSquared();
			waypointIT = it;
		}
		else if (((*it) - owner_->GetPosition()).LengthSquared() < closest)
		{
			closest = ((*it) - owner_->GetPosition()).LengthSquared();
			waypointIT = it;
		}

	}
}