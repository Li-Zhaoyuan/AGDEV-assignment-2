#pragma once

#include "Scene.h"
#include "../FPSCamera.h"
#include <vector>
//#include "../GenericEntity.h"
#include "EntityBase.h"

class SceneManager;
class ShaderProgram;
class Light;
class SceneHighScore : public Scene
{
public:
	virtual ~SceneHighScore();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	SceneHighScore(SceneManager *zeSceneManager);
	static SceneHighScore *cantTouchMain;

	FPSCamera mainCamera;
	Light* lights[2];
	ShaderProgram* currProg;

	std::vector<EntityBase*> m_activeList;
	EntityBase *debuggingMouse; // just to debug the mouse position! Will remove as soon as I am done debugging it!
	// boundaries will act as the right, top, far!
	Vector3 boundaries;
	int gameWidth, gameHeight;
	float timeToChangeScene;
	EntityBase* nyplogo;
	EntityBase* highscore;
};