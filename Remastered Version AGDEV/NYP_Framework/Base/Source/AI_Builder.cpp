#include "AI_Builder.h"
#include "MeshBuilder.h"
#include "StatesStuff\PatrolState.h"
#include "StatesStuff\AttackState.h"
#include "StatesStuff\EscapeState.h"

EntityBase *AI_Builder::thePlayer_ = nullptr;
std::vector<Vector3> *AI_Builder::allTheWayPoints = nullptr;

GenericEntity *AI_Builder::createSimpleAI(const Vector3 &zePos, const Vector3 &zeScale, CPlayerInfo *player)
{
    GenericEntity *zeAI = new GenericEntity(MeshBuilder::GetInstance()->GetMesh("SHIP_1"));
	zeAI->FSM_.setEntityOwner(zeAI);
	zeAI->FSM_.setPlayer(player);
    zeAI->FSM_.addStates(*new PatrolState());   // Adding patrolling state to it
    zeAI->FSM_.addStates(*new AttackState());   // Adding Attacking state to it
	zeAI->FSM_.addStates(*new EscapeState());
    return zeAI;
}