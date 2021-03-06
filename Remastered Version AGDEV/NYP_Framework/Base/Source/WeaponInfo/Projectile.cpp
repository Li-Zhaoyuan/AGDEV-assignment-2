#include "Projectile.h"
#include "MeshBuilder.h"
#include "../SceneGraph/SceneGraph.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#ifdef _DEBUG
#include <iostream>
#endif
#define MAX_LIFESPAN 10.f

size_t Projectile::zeID = 0;

Projectile::Projectile()
    : GenericEntity(MeshBuilder::GetInstance()->GetMesh("BULLET3"))
{
    vel_.SetZero();
    speed_ = 400;
    timespan_ = MAX_LIFESPAN;
    isDone = true;
    name_ = "Projectile"; 
    name_.append(std::to_string(zeID++));
    sceneObjectList = nullptr;
    angleX = angleY = angleZ = 0;
    scale.Set(0.2f, 0.5f, 0.2f);
}

Projectile::Projectile(Mesh *zeMesh)
    : GenericEntity(zeMesh)
{
    vel_.SetZero();
    speed_ = 10;
    timespan_ = MAX_LIFESPAN;
    isDone = true;
    name_ = "Projectile";
    name_.append(std::to_string(zeID++));
    sceneObjectList = nullptr;
}

Projectile::~Projectile()
{

}

void Projectile::Update(double dt)
{
    if (!isDone)
    {
        timespan_ = Math::Clamp(timespan_ - (float)(dt), 0.f, MAX_LIFESPAN);
        if (timespan_ < Math::EPSILON)
        {
            isDone = true;
           return;
        }
        if (!vel_.IsZero())
        {
            position += vel_ * (float)(dt)* speed_;

                    bool shouldRemoveItself = false;
                    for (std::vector<GenericEntity*>::iterator it = sceneObjectList->begin(), end = sceneObjectList->end(); it != end; ++it)
                    {
                        if ((**it) != *this && (*it)->getName().find("Projectile") == std::string::npos)
                        {
							if (((*it)->GetPosition() - this->GetPosition()).LengthSquared() < 25)
							{
								std::cout << "Hit  " << (*it)->getName() << std::endl;

								isDone = true;
								shouldRemoveItself = true;
								(*it)->onNotify("DIED");
								break;
							}
//#ifdef _DEBUG
//                            std::cout << "Object is " << (*it)->getName() << std::endl;
//#endif
//                             SceneNode *zeNodeObj = SceneGraph::GetInstance()->GetNode(*it);
//                             Vector3 thatMinAABB = (*it)->GetPosition() - (*it)->GetScale() /*- scale*/;
//                             Vector3 thatMaxAABB = (*it)->GetPosition() + (*it)->GetScale() /*+ scale*/;
//                             if (zeNodeObj)
//                             {
//								thatMinAABB += zeNodeObj->getRealPosition();
//								thatMaxAABB += zeNodeObj->getRealPosition();
//                             }
//                             Vector3 HitPosition(0, 0, 0);
//                             if (CheckLineSegmentPlane(position, position - (position + vel_ * 200.f), thatMinAABB, thatMaxAABB, HitPosition))
//                             //if (trueRayCasting((*it)))
//                             //if (CheckSphereToSphereCollision(*it))
//                             {
//#ifdef _DEBUG
//                                std::cout << "Hit  " << (*it)->getName() << std::endl;
//#endif
//                                isDone = true;
//                                shouldRemoveItself = true;
//                                (*it)->onNotify("DIED");
//                                break;
//                            }
                        }
                    }
            }
        }
}

void Projectile::Render()
{
    if ((modelMesh && isVisible))
    {
        MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
        //modelStack.PushMatrix();
        //modelStack.Rotate(rotationVector_.x, right_.x, 0, right_.z);
        //modelStack.PushMatrix();
        //modelStack.Rotate(rotationVector_.y - 90.f, 0, 1, 0);

        modelStack.PushMatrix();
        modelStack.Translate(position.x, position.y, position.z);
        modelStack.Scale(scale.x, scale.y, scale.z);

        modelStack.PushMatrix();
        modelStack.Rotate(rotationVector_.x, right_.x, 0, right_.z);
        modelStack.PushMatrix();
        modelStack.Rotate(rotationVector_.y - 180.f, 0, 1, 0);
//        modelStack.PushMatrix();
//            //modelStack.Rotate(angleZ, 0, 1, 0);
//
//                modelStack.PushMatrix();
//                //modelStack.Rotate(angleY, 1, 0, 0);
////                modelStack.Rotate(angleY, vel_.x, 0, vel_.z);
//                    modelStack.PushMatrix();
//                    //modelStack.Rotate(angleX, 0, 0, 1);
        if (GetLODStatus() == true)
        {
            if (theDetailLevel != NO_DETAILS)
                RenderHelper::RenderMesh(GetLODMesh());
        }
        else
        {
            RenderHelper::RenderMesh(modelMesh);
        }
            //        modelStack.PopMatrix();
            //    modelStack.PopMatrix();
            //modelStack.PopMatrix();
            modelStack.PopMatrix();
            modelStack.PopMatrix();

        modelStack.PopMatrix();

    }
}

bool Projectile::onNotify(const std::string &zeEvent)
{
    if (zeEvent.find("RESET") != std::string::npos)
    {
        return true;
    }
    /*else if (zeEvent.find("EXPIRED") )*/
    return false;
}

bool Projectile::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        timespan_ = zeEvent;
        return true;
    }
    else if (zeEvent < -Math::EPSILON)
    {
        speed_ = zeEvent;
        return true;
    }
    return false;
}

bool Projectile::onNotify(const Vector3 &zeEvent1, const Vector3 &zeEvent2)
{
    if (isDone)
    {
        isDone = false;
        vel_ = (zeEvent2 - zeEvent1).Normalize();
        right_ = vel_.Cross(Vector3(0, 1, 0));
        right_.y = 0;
        right_.Normalize();
        angleX = Math::RadianToDegree(acos(vel_.x));
        angleY = Math::RadianToDegree(acos(vel_.y)) - 90.f;
        angleZ = Math::RadianToDegree(acos(vel_.z));
        if (vel_.x < -Math::EPSILON && vel_.z > Math::EPSILON)
            angleX *= -1;
        if (vel_.z < -Math::EPSILON && vel_.x < -Math::EPSILON)
            angleY *= -1;
        if (vel_.z > Math::EPSILON && vel_.x < -Math::EPSILON)
            angleZ *= -1;
        position = zeEvent1;
        timespan_ = MAX_LIFESPAN;
        return true;
    }
    return false;
}

bool Projectile::GetIntersection(const float &fDst1, const float &fDst2, const Vector3 &P1, const Vector3 &P2, Vector3 &Hit)
{
    if ((fDst1 * fDst2) >= Math::EPSILON)
        return false;
    if (fDst1 == fDst2)
        return false;
    Hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
    return true;
}

bool Projectile::InBox(const Vector3 &Hit, const Vector3 &B1, const Vector3 &B2, const int &Axis)
{
    if (Axis == 1 && Hit.x > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y)
        return true;
    if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x)
        return true;
    if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y)
        return true;
    return false;
}

bool Projectile::CheckLineSegmentPlane(const Vector3 &line_start, const Vector3 &line_end, const Vector3 &minAABB, const Vector3 &maxAABB, Vector3 &Hit)
{
    if ((GetIntersection(line_start.x - minAABB.x, line_end.x - minAABB.x, line_start, line_end, Hit) && InBox(Hit, minAABB, maxAABB, 1))
        || (GetIntersection(line_start.y - minAABB.y, line_end.y - minAABB.y, line_start, line_end, Hit) && InBox(Hit, minAABB, maxAABB, 2))
        || (GetIntersection(line_start.z - minAABB.z, line_end.z - minAABB.z, line_start, line_end, Hit) && InBox(Hit, minAABB, maxAABB, 3))
        || (GetIntersection(line_start.x - maxAABB.x, line_end.x - maxAABB.x, line_start, line_end, Hit) && InBox(Hit, minAABB, maxAABB, 1))
        || (GetIntersection(line_start.y - maxAABB.y, line_end.y - maxAABB.y, line_start, line_end, Hit) && InBox(Hit, minAABB, maxAABB, 2))
        || (GetIntersection(line_start.z - maxAABB.z, line_end.z - maxAABB.z, line_start, line_end, Hit) && InBox(Hit, minAABB, maxAABB, 3))
        )
        return true;
    return false;
}

bool Projectile::onNotify(std::vector<GenericEntity*> &zeList)
{
    sceneObjectList = &zeList;
    return true;
}

bool Projectile::onNotify(const float &zeEvent1, const float &zeEvent2)
{
    return GenericEntity::onNotify(zeEvent1, zeEvent2);
}

bool Projectile::trueRayCasting(EntityBase *rhs)
{
    SceneNode *zeNodeObj = SceneGraph::GetInstance()->GetNode(rhs);
    Vector3 rhsPos = rhs->GetPosition();
    if (zeNodeObj)
        rhsPos += zeNodeObj->getRealPosition();
    Vector3 DirectionBetweenThisAndRhs = position - rhsPos;
    //float c = (DirectionBetweenThisAndRhs).LengthSquared() + rhs->GetScale().LengthSquared();
    //float b = 2.f * (vel_ - rhsPos).Length();
    //float a = vel_.LengthSquared();
    float c = (DirectionBetweenThisAndRhs.Dot(DirectionBetweenThisAndRhs)) - (rhs->GetScale().LengthSquared());
    float b = 2.f * (vel_.Dot(position));
    float a = 1;

    std::cout << a << " " << b << " " << c << std::endl;
    float d = (b*b) - (4 * a * c);
    if (d < Math::EPSILON)
        return false;
    if (a < Math::EPSILON)
        return false;

    float sqrtOFd = sqrt(d);
    float t0 = (-b - sqrtOFd) / (2/* * a*/);
    float t1 = (-b + sqrtOFd) / (2/* * a*/);

    if (t1 < 0 || t0 > 10000.f)
        return false;
    
    return true;
}

bool Projectile::onNotify(const Vector3 &zeEvent)
{
    rotationVector_ = zeEvent;
    return true;
}

bool Projectile::CheckSphereToSphereCollision(EntityBase *rhs)
{
    SceneNode *zeNodeObj = SceneGraph::GetInstance()->GetNode(rhs);
    Vector3 rhsPos = rhs->GetPosition();
    if (zeNodeObj)
        rhsPos += zeNodeObj->getRealPosition();

    float Distsq = (position - rhsPos).LengthSquared();
    if (Distsq <= ((scale.x * scale.x) + (rhs->GetScale().x * rhs->GetScale().x)))
        return true;

    return false;
}