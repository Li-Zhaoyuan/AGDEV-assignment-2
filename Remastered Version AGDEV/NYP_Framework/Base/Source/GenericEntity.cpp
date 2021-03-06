#include "GenericEntity.h"
#include "MeshBuilder.h"
#include "EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "SceneGraph\SceneGraph.h"
#ifdef _DEBUG
#include <assert.h>
#endif
#include "SceneManager.h"

static const int ScoreByGeneric = 2;

GenericEntity::GenericEntity(Mesh* _modelMesh)
	: modelMesh(_modelMesh)
{
    isDone = false;
    boundary_ = nullptr;
    howManyLives = 10;
	isVisible = true;
	isKilledByBullet = true;
	levelOfDetail_Distances[0] = 0.f;
	levelOfDetail_Distances[1] = 0.f;
	health = 100;
}

GenericEntity::~GenericEntity()
{
}

void GenericEntity::Update(double _dt)
{
    FSM_.Update(_dt);
}

void GenericEntity::Render()
{
	if (modelMesh  && isVisible&& !isDone)
    {
        MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
        modelStack.PushMatrix();
        modelStack.Translate(position.x, position.y, position.z);
        modelStack.Scale(scale.x, scale.y, scale.z);
		modelStack.Rotate(rotation, 0, 1, 0);
		modelStack.Rotate(rotation2, 0, 0, 1);
		if (GetLODStatus() == true)
		{
			if (theDetailLevel != NO_DETAILS)
				RenderHelper::RenderMesh(GetLODMesh());
		}
		else
		{
			RenderHelper::RenderMesh(modelMesh);
		}
        modelStack.PopMatrix();
    }
}


// Set the maxAABB and minAABB
//void GenericEntity::SetAABB(Vector3 maxAABB, Vector3 minAABB)
//{
//	this->maxAABB = maxAABB;
//	this->minAABB = minAABB;
//}

GenericEntity* Create::Entity(	const std::string& _meshName, 
								const Vector3& _position,
								const Vector3& _scale)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	GenericEntity* result = new GenericEntity(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);
	result->SetCollider(false);
	//EntityManager::GetInstance()->AddEntity(result);
	return result;
}

bool GenericEntity::onNotify(EntityBase &zeEvent)
{
    if (zeEvent.getName().find("Boundary") != std::string::npos)
    {
        boundary_ = &zeEvent;
        return true;
    }
    return false;
}

bool GenericEntity::onNotify(const std::string &zeEvent)
{
    if (zeEvent.find("DIED") != std::string::npos && !isDone)
    {
        //--howManyLives;
		health -= 10;
		if (health == 0)
        {
            isDone = true;
			isShot = true;
			SceneNode* temp = SceneGraph::GetInstance()->GetNode(this);
			if (temp != NULL)
			{
				temp->setAllChildToShot(this, true);
			}
            //return true;
            //std::string zeScore = "SCORE:";
            //zeScore.append(to_string(ScoreByGeneric));
            return SceneManager::GetInstance()->GetCurrScene()->onNotify("ASTEROID_DIED");
        }
    }
    else if (zeEvent.find("RESET") != std::string::npos)
    {
		health = 100;
        isDone = false;
        return true;
    }
    else if (zeEvent.find("DESTROY_SHIP") != std::string::npos)
    {
        std::string zeScore = "SCORE:";
        isDone = true;
        zeScore.append(std::to_string(ScoreByGeneric));
		isShot = false;
		SceneNode* temp = SceneGraph::GetInstance()->GetNode(this);
		if (temp != NULL)
		{
			temp->setAllChildToShot(this, false);
		}
        //std::cout << name_ << zeEvent << std::endl;
		//SceneGraph::GetInstance()->GetNode(this)->DeleteAllChildren();
		//SceneGraph::GetInstance()->DeleteNode(this);
        return SceneManager::GetInstance()->GetCurrScene()->onNotify(zeScore);
    }
    return false;
}

bool GenericEntity::onNotify(const Vector3 &zeEvent1, const Vector3 &zeEvent2)
{
	posOfPlayer = zeEvent1;
	targetOfPlayer = zeEvent2;
	SceneNode* temp = SceneGraph::GetInstance()->GetNode(this);
	if (temp == NULL)
	{
		Vector3 camDir = targetOfPlayer - posOfPlayer;
		Vector3 distToObj = position - posOfPlayer;

		if (camDir.Dot(distToObj) > 0)
		{
			isVisible = true;
			return true;
		}
		isVisible = false;
		return false;
	}
	else
	{
		Vector3 camDir = targetOfPlayer - posOfPlayer;
		Vector3 distToObj = temp->getRealPosition() - posOfPlayer;

		if (camDir.Dot(distToObj) > 0)
		{
			isVisible = true;
			return true;
		}
		isVisible = false;
		return false;
	}
}

bool GenericEntity::onNotify(const Vector3 &zeEvent)
{
	if (isVisible)
	{
		SceneNode* temp = SceneGraph::GetInstance()->GetNode(this);
		if (temp == NULL)
		{
			Vector3 PlayerPos = zeEvent;
			Vector3 dist = position - PlayerPos;
			if (dist.LengthSquared() < levelOfDetail_Distances[0] * levelOfDetail_Distances[0])
			{
				SetDetailLevel(HIGH_DETAILS);
			}
			else if (dist.LengthSquared() < levelOfDetail_Distances[1] * levelOfDetail_Distances[1])
			{
				SetDetailLevel(MID_DETAILS);
			}
			else
			{
				SetDetailLevel(LOW_DETAILS);
			}
		}
		else
		{
			Vector3 PlayerPos = zeEvent;
			Vector3 dist = temp->getRealPosition() - PlayerPos;
			if (dist.LengthSquared() < levelOfDetail_Distances[0] * levelOfDetail_Distances[0])
			{
				SetDetailLevel(HIGH_DETAILS);
			}
			else if (dist.LengthSquared() < levelOfDetail_Distances[1] * levelOfDetail_Distances[1])
			{
				SetDetailLevel(MID_DETAILS);
			}
			else
			{
				SetDetailLevel(LOW_DETAILS);
			}
		}
	}
	return true;
}

bool GenericEntity::onNotify(const float &zeEvent1, const float &zeEvent2)
{
	levelOfDetail_Distances[0] = zeEvent1;
	levelOfDetail_Distances[1] = zeEvent2;
	return true;
}