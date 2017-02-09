#pragma once

#include <string>
#include "EntityBase.h"
#include <vector>

class CPlayerInfo;
class GenericEntity;
class GenericComponent
{
public:
    GenericComponent();
    GenericComponent(const std::string &zeName);
    GenericComponent(const std::string &zeName, EntityBase *zeOwner);
    virtual ~GenericComponent();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    void setName(const std::string zeName);
    void setEntityOwner(EntityBase *zeOwner);
	void setPlayer(CPlayerInfo *player);
	void setVectorOfBullets(std::vector<GenericEntity*> *m_activeList);
	void setIsHitByPlayer(bool toggle);

    virtual bool onNotify(const std::string &zeEvent) { return false; };
    virtual bool onNotify(const int &zeEvent) { return false; };
    virtual bool onNotify(const float &zeEvent) { return false; };
    virtual bool onNotify(GenericComponent &zeEvent) { return false; };
    virtual bool onNotify(EntityBase &zeEvent) { return false; }

    std::string getName();
    EntityBase *getOwner();
	CPlayerInfo *getPlayer();
	std::vector<GenericEntity*> getVectorOfBullets();
	bool getIsHitByPlayer();

protected:
    std::string name_;
    EntityBase *owner_;
	CPlayerInfo *zePlayer;
	std::vector<GenericEntity*> *m_activeList;
	//bool isHitByPlayer = false;
};
