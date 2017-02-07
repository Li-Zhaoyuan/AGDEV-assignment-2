#include "PatrolState.h"

PatrolState::PatrolState()
{
    name_ = "PATROL";
    owner_ = nullptr;
    Own_ID_ = PATROL_ID_;
    WayPointsInMap = nullptr;
    IndexOfWaypoint = 0;
    thePlayer_ = nullptr;
    influenceRadius = 4;
    wayPtInfluenceSq = 4;
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