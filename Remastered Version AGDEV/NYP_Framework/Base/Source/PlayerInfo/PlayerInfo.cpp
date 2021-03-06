#include "PlayerInfo.h"
#include <iostream>

#include "MouseController.h"
#include "KeyboardController.h"
#include "Mtx44.h"
#include "../../lua/LuaInterface.h"

// Allocating and initializing CPlayerInfo's static data member.  
// The pointer is allocated but not the object's constructor.
//CPlayerInfo *CPlayerInfo::s_instance = 0;
#define CAMERA_SPEED 200.f
#ifndef _DEBUG
#define _IN_RELEASE_REDUCE_SPEED 0.05f
#endif

CPlayerInfo::CPlayerInfo(void)
	: m_dSpeed(100.0)
	, m_dAcceleration(10.0)
	, m_bJumpUpwards(false)
	, m_dJumpSpeed(10.0)
	, m_dJumpAcceleration(-10.0)
	, m_bFallDownwards(false)
	, m_dFallSpeed(0.0)
	, m_dFallAcceleration(-10.0)
	, attachedCamera(NULL)
	, m_pTerrain(NULL)
	, keyMoveForward('W')
	, keyMoveBackward('S')
	, keyMoveLeft('A')
	, keyMoveRight('D')
	, keyReload('E')
	, keyReset('P')
	, ammo(15)
	, maxClips(1)
	, fireRate(0.2f)

{
	keyMoveForward = LuaInterface::GetInstance()->getCharValue("moveForward");
	keyMoveBackward = LuaInterface::GetInstance()->getCharValue("moveBackward");
	keyMoveLeft = LuaInterface::GetInstance()->getCharValue("moveLeft");
	keyMoveRight = LuaInterface::GetInstance()->getCharValue("moveRight");
	
	
	mainWeapon = new Weapon();
	mainWeapon->onNotify(fireRate);
	mainWeapon->onNotify(ammo, maxClips);
}

CPlayerInfo::~CPlayerInfo(void)
{
	m_pTerrain = NULL;
    delete mainWeapon;
}

// Initialise this class instance
void CPlayerInfo::Init(void)
{
	//// Set the default values
	//defaultPosition.Set(0,0,10);
	//defaultTarget.Set(0,0,0);
	//defaultUp.Set(0,1,0);

	//// Set the current values
	//position.Set(0, 0, 10);
	//target.Set(0, 0, 0);
	//up.Set(0, 1, 0);

	//// Set Boundary
	//maxBoundary.Set(1,1,1);
	//minBoundary.Set(-1, -1, -1);
}

// Returns true if the player is on ground
bool CPlayerInfo::isOnGround(void)
{



	return false;
}

// Returns true if the player is jumping upwards
bool CPlayerInfo::isJumpUpwards(void)
{



	return false;
}

// Returns true if the player is on freefall
bool CPlayerInfo::isFreeFall(void)
{



	return false;
}

// Set the player's status to free fall mode
void CPlayerInfo::SetOnFreeFall(bool isOnFreeFall)
{





}

// Set the player to jumping upwards
void CPlayerInfo::SetToJumpUpwards(bool isOnJumpUpwards)
{





}

//// Set position
//void CPlayerInfo::SetPos(const Vector3& pos)
//{
//	position = pos;
//}
//
//// Set target
//void CPlayerInfo::SetTarget(const Vector3& target)
//{
//	this->target = target;
//}
//
//// Set position
//void CPlayerInfo::SetUp(const Vector3& up)
//{
//	this->up = up;
//}

// Set m_dJumpAcceleration of the player
void CPlayerInfo::SetJumpAcceleration(const double m_dJumpAcceleration)
{
	this->m_dJumpAcceleration = m_dJumpAcceleration;
}

// Set Fall Acceleration of the player
void CPlayerInfo::SetFallAcceleration(const double m_dFallAcceleration)
{
	this->m_dFallAcceleration = m_dFallAcceleration;
}

//// Set the boundary for the player info
//void CPlayerInfo::SetBoundary(Vector3 max, Vector3 min)
//{
//	maxBoundary = max;
//	minBoundary = min;
//}

// Set the terrain for the player info
void CPlayerInfo::SetTerrain(GroundEntity* m_pTerrain)
{






}

// Stop the player's movement
void CPlayerInfo::StopVerticalMovement(void)
{
	m_bJumpUpwards = false;
	m_bFallDownwards = false;
}

// Reset this player instance to default
void CPlayerInfo::Reset(void)
{
	// Set the current values to default values
	//position = defaultPosition;
	//target = defaultTarget;
	//up = defaultUp;

	// Stop vertical movement too
	mainWeapon->onNotify(ammo, maxClips);
    StopVerticalMovement();
}
void CPlayerInfo::refillAmmo()
{
	mainWeapon->onNotify(ammo, maxClips);
}

// Get position x of the player
//Vector3 CPlayerInfo::GetPos(void) const
//{
//	return position;
//}

// Get target
//Vector3 CPlayerInfo::GetTarget(void) const
//{
//	return target;
//}
// Get Up
//Vector3 CPlayerInfo::GetUp(void) const
//{
//	return up;
//}

// Get m_dJumpAcceleration of the player
double CPlayerInfo::GetJumpAcceleration(void) const
{
	return m_dJumpAcceleration;
}

// Update Jump Upwards
void CPlayerInfo::UpdateJumpUpwards(double dt)
{
	if (m_bJumpUpwards == false)
		return;

	// Update position and target y values
	// Use SUVAT equation to update the change in position and target
	// s = u * t + 0.5 * a * t ^ 2


	// Use this equation to calculate final velocity, v
	// SUVAT: v = u + a * t;
	// v is m_dJumpSpeed AFTER updating using SUVAT where u is the initial speed and is equal to m_dJumpSpeed

	// Check if the jump speed is less than zero, then it should be falling
	if (m_dJumpSpeed < 0.0)
	{




	}
}

// Update FreeFall
void CPlayerInfo::UpdateFreeFall(double dt)
{
	if (m_bFallDownwards == false)
		return;

	// Update position and target y values
	// Use SUVAT equation to update the change in position and target
	// s = u * t + 0.5 * a * t ^ 2


	// Use this equation to calculate final velocity, v
	// SUVAT: v = u + a * t;
	// v is m_dJumpSpeed AFTER updating using SUVAT where u is the initial speed and is equal to m_dJumpSpeed

	// Check if the jump speed is below terrain, then it should be reset to terrain height
	//if (position.y < m_pTerrain->GetTerrainHeight(position))
	//{





	//}
}

/********************************************************************************
 Hero Update
 ********************************************************************************/
void CPlayerInfo::Update(double dt)
{
	
	double mouse_diff_x, mouse_diff_y;
	MouseController::GetInstance()->GetMouseDelta(mouse_diff_x, mouse_diff_y);

	double camera_yaw = mouse_diff_x * 0.0174555555555556;		// 3.142 / 180.0
	double camera_pitch = mouse_diff_y * 0.0174555555555556;	// 3.142 / 180.0

	// Update the position if the WASD buttons were activated
	if (KeyboardController::GetInstance()->IsKeyDown(keyMoveForward) ||
		KeyboardController::GetInstance()->IsKeyDown(keyMoveBackward) ||
		KeyboardController::GetInstance()->IsKeyDown(keyMoveRight) ||
		KeyboardController::GetInstance()->IsKeyDown(keyMoveLeft))
	{
        Vector3 viewVector = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
        Vector3 normalizedView = viewVector.Normalized();
        normalizedView.y = 0;
		Vector3 rightUV(0,0,0);
		if (KeyboardController::GetInstance()->IsKeyDown(keyMoveForward))
		{
            attachedCamera->GetCameraPos() += normalizedView * (float)m_dSpeed * (float)dt;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown(keyMoveBackward))
		{
            attachedCamera->GetCameraPos() -= normalizedView * (float)m_dSpeed * (float)dt;
		}
		if (KeyboardController::GetInstance()->IsKeyDown(keyMoveLeft))
		{
            if (rightUV.IsZero())
                rightUV = (normalizedView).Cross(attachedCamera->GetCameraUp());
			rightUV.y = 0;
			rightUV.Normalize();
            attachedCamera->GetCameraPos() -= rightUV * (float)m_dSpeed * (float)dt;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown(keyMoveRight))
		{
            if (rightUV.IsZero())
                rightUV = (normalizedView).Cross(attachedCamera->GetCameraUp());
			rightUV.y = 0;
			rightUV.Normalize();
			attachedCamera->GetCameraPos() += rightUV * (float)m_dSpeed * (float)dt;
		}
		// Constrain the position
		Constrain();
		// Update the target
        attachedCamera->GetCameraTarget() = attachedCamera->GetCameraPos() + viewVector;
	}

	//// Rotate the view direction
	//if (KeyboardController::GetInstance()->IsKeyDown(VK_LEFT) ||
	//	KeyboardController::GetInstance()->IsKeyDown(VK_RIGHT) ||
	//	KeyboardController::GetInstance()->IsKeyDown(VK_UP) ||
	//	KeyboardController::GetInstance()->IsKeyDown(VK_DOWN))
	//{
	//	Vector3 viewUV = (target - position).Normalized();
	//	Vector3 rightUV;
	//	if (KeyboardController::GetInstance()->IsKeyDown(VK_LEFT))
	//	{
	//		float yaw = (float)m_dSpeed * (float)dt;
	//		Mtx44 rotation;
	//		rotation.SetToRotation(yaw, 0, 1, 0);
	//		viewUV = rotation * viewUV;
	//		target = position + viewUV;
	//		rightUV = viewUV.Cross(up);
	//		rightUV.y = 0;
	//		rightUV.Normalize();
	//		up = rightUV.Cross(viewUV).Normalized();
	//	}
	//	else if (KeyboardController::GetInstance()->IsKeyDown(VK_RIGHT))
	//	{
	//		float yaw = (float)(-m_dSpeed * (float)dt);
	//		Mtx44 rotation;
	//		rotation.SetToRotation(yaw, 0, 1, 0);
	//		viewUV = rotation * viewUV;
	//		target = position + viewUV;
	//		rightUV = viewUV.Cross(up);
	//		rightUV.y = 0;
	//		rightUV.Normalize();
	//		up = rightUV.Cross(viewUV).Normalized();
	//	}
	//	if (KeyboardController::GetInstance()->IsKeyDown(VK_UP))
	//	{
	//		float pitch = (float)(m_dSpeed * (float)dt);
	//		rightUV = viewUV.Cross(up);
	//		rightUV.y = 0;
	//		rightUV.Normalize();
	//		up = rightUV.Cross(viewUV).Normalized();
	//		Mtx44 rotation;
	//		rotation.SetToRotation(pitch, rightUV.x, rightUV.y, rightUV.z);
	//		viewUV = rotation * viewUV;
	//		target = position + viewUV;
	//	}
	//	else if (KeyboardController::GetInstance()->IsKeyDown(VK_DOWN))
	//	{
	//		float pitch = (float)(-m_dSpeed * (float)dt);
	//		rightUV = viewUV.Cross(up);
	//		rightUV.y = 0;
	//		rightUV.Normalize();
	//		up = rightUV.Cross(viewUV).Normalized();
	//		Mtx44 rotation;
	//		rotation.SetToRotation(pitch, rightUV.x, rightUV.y, rightUV.z);
	//		viewUV = rotation * viewUV;
	//		target = position + viewUV;
	//	}
	//}

	////Update the camera direction based on mouse move
	{
        Vector3 viewUV = (attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos()).Normalize();
		Vector3 rightUV, theDirection, tempDistToTargetz;


		{
			float yaw = (float)(-m_dSpeed * camera_yaw * (float)dt);
#ifdef _DEBUG
            //yaw *= m_dSpeed;
#else
            //yaw *= (float)m_dSpeed * _IN_RELEASE_REDUCE_SPEED;
            if (1 / dt >= 30)
                yaw /= -1.5f;
#endif
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			viewUV = rotation * viewUV;
            attachedCamera->GetCameraTarget() = attachedCamera->GetCameraPos() + viewUV;
			rightUV = viewUV.Cross(attachedCamera->GetCameraUp());
			rightUV.y = 0;
			rightUV.Normalize();
            attachedCamera->GetCameraUp() = rightUV.Cross(viewUV).Normalized();
			attachedCamera->GetCameraRotation().y += yaw;
		}
		{
			float pitch = (float)(-m_dSpeed * camera_pitch * (float)dt);
#ifdef _DEBUG
            //pitch *= (float)m_dSpeed;
#else
            //pitch *= (float)m_dSpeed * _IN_RELEASE_REDUCE_SPEED;
            if (1 / dt >= 30)
                pitch /= 1.2f;
#endif
            rightUV = viewUV.Cross(attachedCamera->GetCameraUp());
			rightUV.y = 0;
			rightUV.Normalize();
            attachedCamera->GetCameraUp() = rightUV.Cross(viewUV).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, rightUV.x, rightUV.y, rightUV.z);
			viewUV = rotation * viewUV;
			if (attachedCamera->GetCameraPos().y + viewUV.y < 0.5f
				&& attachedCamera->GetCameraPos().y + viewUV.y > -0.5f)
			{
				attachedCamera->GetCameraTarget() = attachedCamera->GetCameraPos() + viewUV;
				attachedCamera->GetCameraRotation().x += pitch;
			}
		}
		theDirection = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
		theDirection.Normalize();

		
		
		/*attachedCamera->GetCameraRotation().x = Math::RadianToDegree(acos(theDirection.x / theDirection.Length()));
		if ((theDirection.x < 0) && (theDirection.z > 0))
			attachedCamera->GetCameraRotation().x *= -1.0f;
		attachedCamera->GetCameraRotation().y = Math::RadianToDegree(acos(theDirection.y / theDirection.Length()));
		attachedCamera->GetCameraRotation().z = Math::RadianToDegree(acos(theDirection.z / theDirection.Length()));
		if ((theDirection.z < 0) && (theDirection.x < 0))
			attachedCamera->GetCameraRotation().y *= -1.0f;
		if ((theDirection.z > 0) && (theDirection.x < 0))
			attachedCamera->GetCameraRotation().z *= -1.0f;*/
		attachedCamera->GetCameraRight() = rightUV;
	}

	// If the user presses SPACEBAR, then make him jump
	//if (KeyboardController::GetInstance()->IsKeyDown(VK_SPACE) &&
	//	position.y == m_pTerrain->GetTerrainHeight(position))
	//{

	//}

	// Update the weapons
	if (KeyboardController::GetInstance()->IsKeyReleased('R'))
	{
	}

	// if Mouse Buttons were activated, then act on them
    mainWeapon->Update(dt);
	if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
	{
        mainWeapon->onNotify("FIRE");
	}
	else if (MouseController::GetInstance()->IsButtonPressed(MouseController::RMB))
	{

	}
    if (KeyboardController::GetInstance()->IsKeyDown(keyReload))
    {
        mainWeapon->onNotify("RELOAD");
    }
    // If the user presses R key, then reset the view to default values
	if (KeyboardController::GetInstance()->IsKeyDown(keyReset))
	{
		Reset();
	}

	// If a camera is attached to this playerInfo class, then update it
	//if (attachedCamera)
	//{
	//	attachedCamera->SetCameraPos(position);
	//	attachedCamera->SetCameraTarget(target);
	//}

    // Updating the player entity because the codes are just way too messy as of this point
    thePlayerEntity.SetPosition(attachedCamera->GetCameraPos());
}

// Constrain the position within the borders
void CPlayerInfo::Constrain(void)
{
    if (attachedCamera->GetCameraPos().x > boundary_.x)
    {
        Vector3 viewVector = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
        attachedCamera->GetCameraPos().x = boundary_.x - Math::EPSILON;
        attachedCamera->GetCameraTarget() = attachedCamera->GetCameraPos() + viewVector;
    }
    else if (attachedCamera->GetCameraPos().x < -boundary_.x)
    {
        Vector3 viewVector = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
        attachedCamera->GetCameraPos().x = -boundary_.x + Math::EPSILON;
        attachedCamera->GetCameraTarget() = attachedCamera->GetCameraPos() + viewVector;
    }
    if (attachedCamera->GetCameraPos().z > boundary_.z)
    {
        Vector3 viewVector = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
        attachedCamera->GetCameraPos().z = boundary_.z - Math::EPSILON;
        attachedCamera->GetCameraTarget() = attachedCamera->GetCameraPos() + viewVector;
    }
    else if (attachedCamera->GetCameraPos().z < -boundary_.z)
    {
        Vector3 viewVector = attachedCamera->GetCameraTarget() - attachedCamera->GetCameraPos();
        attachedCamera->GetCameraPos().z = -boundary_.z + Math::EPSILON;
        attachedCamera->GetCameraTarget() = attachedCamera->GetCameraPos() + viewVector;
    }

}

void CPlayerInfo::AttachCamera(FPSCamera* _cameraPtr)
{
	attachedCamera = _cameraPtr;
}

void CPlayerInfo::DetachCamera()
{
	attachedCamera = nullptr;
}

FPSCamera &CPlayerInfo::GetCurrCamera()
{
    return *attachedCamera;
}

size_t CPlayerInfo::getCurrNumBullet()
{
    return mainWeapon->getNumCurrBullets();
}

size_t CPlayerInfo::getCurrNumClips()
{
    return mainWeapon->getNumCurrMagazine();
}

void CPlayerInfo::setBoundary(Vector3 &zeBounds)
{
    boundary_ = zeBounds * 0.5f;
    boundary_ -= boundary_ * 0.1f;
}