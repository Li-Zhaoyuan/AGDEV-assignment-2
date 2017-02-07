#include "AI_Builder.h"
#include "MeshBuilder.h"
#include "StatesStuff\PatrolState.h"
#include "StatesStuff\AttackState.h"

EntityBase *AI_Builder::thePlayer_ = nullptr;
std::vector<Vector3> *AI_Builder::allTheWayPoints = nullptr;

GenericEntity *AI_Builder::createSimpleAI(const Vector3 &zePos, const Vector3 &zeScale)
{
    GenericEntity *zeAI = new GenericEntity(MeshBuilder::GetInstance()->GetMesh("ANDROID"));
    zeAI->FSM_.addStates(*new PatrolState());   // Adding patrolling state to it
    zeAI->FSM_.addStates(*new AttackState());   // Adding Attacking state to it
    return zeAI;
}