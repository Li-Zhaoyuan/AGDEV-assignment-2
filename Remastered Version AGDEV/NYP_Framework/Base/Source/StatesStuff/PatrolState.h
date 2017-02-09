#pragma once

#include "StateComponent.h"
#include <list>

#ifndef PATROL_ID_
#define PATROL_ID_ 0
#endif

class PatrolState : public StateComponent
{
public:
    PatrolState();
    virtual ~PatrolState();

    virtual void Update(double dt);
    virtual void Exit();

    virtual bool onNotify(const float &zeEvent);
    virtual bool onNotify(EntityBase &zeEvent);

	void initWayPoints();

private:
    std::list<Vector3> AllWayPoints;
    std::vector<Vector3> WayPointsInMap;
	std::vector<Vector3>::iterator waypointIT;
    size_t IndexOfWaypoint;
    float wayPtInfluenceSq;   // Helps to offset if the entity have reached the destination more or less
    EntityBase *thePlayer_;
	Vector3 vel;
	bool isAtWayPoint;
};