#pragma once

#include "GenericEntity.h"
#include "PlayerInfo\PlayerInfo.h"

class AI_Builder
{
public:
    static GenericEntity *createSimpleAI(const Vector3 &zePos, const Vector3 &zeScale, CPlayerInfo* player);

    static EntityBase *thePlayer_;
    static std::vector<Vector3> *allTheWayPoints;
};