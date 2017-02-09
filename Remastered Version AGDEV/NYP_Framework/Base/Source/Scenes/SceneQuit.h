#pragma once

#include "Scene.h"
#include "../FPSCamera.h"
#include <vector>
//#include "../GenericEntity.h"
#include "EntityBase.h"

class SceneManager;
class ShaderProgram;
class Light;
class SceneQuit : public Scene
{
public:
	virtual ~SceneQuit();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	SceneQuit(SceneManager *zeSceneManager);
	static SceneQuit *cantTouchMain;

	FPSCamera mainCamera;
	Light* lights[2];
	ShaderProgram* currProg;

	std::vector<EntityBase*> m_activeList;
	std::vector<EntityBase*> selectionList;
	std::vector<EntityBase *>::iterator selectIter;
	EntityBase *debuggingMouse; // just to debug the mouse position! Will remove as soon as I am done debugging it!
	// boundaries will act as the right, top, far!
	Vector3 boundaries;
	int gameWidth, gameHeight;
	float timeToChangeScene;
	EntityBase* nyplogo;
	EntityBase* quit;
	EntityBase* areyousure;
	EntityBase* yes;
	EntityBase* no;
	EntityBase * selectkey;

	char moveKeyLeft;
	char moveKeyRight;
	char moveKeyEnter;

	float keypress;
};