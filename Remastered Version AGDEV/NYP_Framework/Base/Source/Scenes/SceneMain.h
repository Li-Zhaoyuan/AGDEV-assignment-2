#pragma once

#include "Scene.h"
#include "../FPSCamera.h"
#include <vector>
//#include "../GenericEntity.h"
#include "EntityBase.h"

class SceneManager;
class ShaderProgram;
class Light;
class SceneMain : public Scene
{
public:
    virtual ~SceneMain();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

protected:
    SceneMain(SceneManager *zeSceneManager);
    static SceneMain *cantTouchMain;

    FPSCamera mainCamera;
    Light* lights[2];
    ShaderProgram* currProg;

    std::vector<EntityBase*> m_activeList;
    EntityBase *debuggingMouse; // just to debug the mouse position! Will remove as soon as I am done debugging it!
    // boundaries will act as the right, top, far!
    Vector3 boundaries;
    int gameWidth, gameHeight;
	EntityBase * title;
	EntityBase * startbutton;
	EntityBase * highscorebutton;
	EntityBase * quitbutton;
	EntityBase * optionsbutton;
	EntityBase * selectkey;

	std::vector<EntityBase *> selectionList;
	std::vector<EntityBase *>::iterator selectIter;

	char moveKeyUp;
	char moveKeyDown;
	char moveKeyEnter;

	float keypress;
	float titleScale;

	bool showSubScene;
};