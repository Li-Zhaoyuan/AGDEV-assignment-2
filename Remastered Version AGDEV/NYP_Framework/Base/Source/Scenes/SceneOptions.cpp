#include "SceneOptions.h"
#include "SceneManager.h"
#include "GL\glew.h"

#include "../Application.h"

#include "MeshBuilder.h"
#include "Utility.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "MyMath.h"
#include "../Light.h"
#include "../TextEntity.h"
#include "../GenericEntity.h"
#include <sstream>
#include "../../lua/LuaInterface.h"
#include "../MusicsStuff/MusicSystem.h"

SceneOptions *SceneOptions::cantTouchMain = new SceneOptions(SceneManager::GetInstance());

SceneOptions::SceneOptions(SceneManager *zeSceneManager)
{
	Scene_name_ = "Options";
	zeSceneManager->AddSubScene(Scene_name_, this);
}

SceneOptions::~SceneOptions()
{
}

void SceneOptions::Init()
{
	currProg = GraphicsManager::GetInstance()->LoadShader("default", "Shader//Texture.vertexshader", "Shader//Texture.fragmentshader");

	// Tell the shader program to store these uniform locations
	currProg->AddUniform("MVP");
	currProg->AddUniform("MV");
	currProg->AddUniform("MV_inverse_transpose");
	currProg->AddUniform("material.kAmbient");
	currProg->AddUniform("material.kDiffuse");
	currProg->AddUniform("material.kSpecular");
	currProg->AddUniform("material.kShininess");
	currProg->AddUniform("lightEnabled");
	currProg->AddUniform("numLights");
	currProg->AddUniform("lights[0].type");
	currProg->AddUniform("lights[0].position_cameraspace");
	currProg->AddUniform("lights[0].color");
	currProg->AddUniform("lights[0].power");
	currProg->AddUniform("lights[0].kC");
	currProg->AddUniform("lights[0].kL");
	currProg->AddUniform("lights[0].kQ");
	currProg->AddUniform("lights[0].spotDirection");
	currProg->AddUniform("lights[0].cosCutoff");
	currProg->AddUniform("lights[0].cosInner");
	currProg->AddUniform("lights[0].exponent");
	currProg->AddUniform("lights[1].type");
	currProg->AddUniform("lights[1].position_cameraspace");
	currProg->AddUniform("lights[1].color");
	currProg->AddUniform("lights[1].power");
	currProg->AddUniform("lights[1].kC");
	currProg->AddUniform("lights[1].kL");
	currProg->AddUniform("lights[1].kQ");
	currProg->AddUniform("lights[1].spotDirection");
	currProg->AddUniform("lights[1].cosCutoff");
	currProg->AddUniform("lights[1].cosInner");
	currProg->AddUniform("lights[1].exponent");
	currProg->AddUniform("colorTextureEnabled");
	currProg->AddUniform("colorTexture");
	currProg->AddUniform("textEnabled");
	currProg->AddUniform("textColor");

	// Tell the graphics manager to use the shader we just loaded
	GraphicsManager::GetInstance()->SetActiveShader("default");

	mainCamera.Init(Vector3(0, 0, 9.95f), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//m_activeList.push_back(Create::Entity("reference", Vector3(0, 0, 0)));

	boundaries.Set(400, 300, 10);   // We will just take the resolution of 800 by 600

	//m_activeList.push_back(Create::Text2DObject("text", Vector3(-boundaries.x, -boundaries.y + 50, 0), "Press Space To Start", Vector3(25, 25, 1), Color(0, 1, 0)));
	debuggingMouse = Create::Text2DObject("text", Vector3(-boundaries.x, -boundaries.y + 75, 0), "Mouse", Vector3(25, 25, 1), Color(0, 1, 0));
	//m_activeList.push_back(debuggingMouse);

	gameWidth = Application::GetInstance().GetWindowWidth();
	gameHeight = Application::GetInstance().GetWindowHeight();
	//Application::GetInstance().hideMouse(false);
	//	GenericEntity* test = Create::Entity(,,)
	float worldX = ((float)(gameWidth / 2) / gameWidth * boundaries.x * 2) - boundaries.x;
	float worldY = ((float)(gameHeight - (gameHeight/2)) / gameHeight * boundaries.y * 2) - boundaries.y;

	float startX = ((float)(gameWidth*3 / 4) / gameWidth * boundaries.x * 2) - boundaries.x;
	float startY = ((float)(gameHeight - (gameHeight * 0.4f)) / gameHeight * boundaries.y * 2) - boundaries.y;

	float msgX = ((float)(gameWidth * 3 / 4) / gameWidth * boundaries.x * 2) - boundaries.x;
	float msgY = ((float)(gameHeight - (gameHeight * 0.6f)) / gameHeight * boundaries.y * 2) - boundaries.y;
	
	float yesX = ((float)(gameWidth * (7) / 8) / gameWidth * boundaries.x * 2) - boundaries.x;
	float yesY = ((float)(gameHeight - (gameHeight * 0.8f)) / gameHeight * boundaries.y * 2) - boundaries.y;

	float noX = ((float)(gameWidth * (5) / 8) / gameWidth * boundaries.x * 2) - boundaries.x;
	float noY = ((float)(gameHeight - (gameHeight * 0.8f)) / gameHeight * boundaries.y * 2) - boundaries.y;
	
	float selectX = ((float)(gameWidth * (5) / 8) / gameWidth * boundaries.x * 2) - boundaries.x;
	float selectY = ((float)(gameHeight - (gameHeight * 0.8f)) / gameHeight * boundaries.y * 2) - boundaries.y;

	nyplogo = Create::Entity("LOGO", Vector3(worldX, worldY, 0.f), Vector3(gameWidth*0.1 * (360 / 77), gameWidth*0.1, 5));
	quit = Create::Entity("OPTIONS", Vector3(startX, startY, 0.f), Vector3(gameWidth*0.02 * (800 / 199), gameWidth*0.02, 5));
	areyousure = Create::Entity("ENABLE", Vector3(msgX, msgY, 0.f), Vector3(gameWidth*0.02 * (237 / 38), gameWidth*0.02, 5));
	yes = Create::Entity("YES", Vector3(yesX, yesY, 0.f), Vector3(gameWidth*0.02 * (800 / 199), gameWidth*0.02, 5));
	no = Create::Entity("NO", Vector3(noX, noY, 0.f), Vector3(gameWidth*0.02 * (800 / 199), gameWidth*0.02, 5));
	selectkey = Create::Entity("SELECT", Vector3(selectX, selectY, 0.f), Vector3(gameWidth*0.02 * (800 / 199)* 1.2f, gameWidth*0.02, 5));
	m_activeList.push_back(quit);
	m_activeList.push_back(areyousure);
	m_activeList.push_back(yes);
	m_activeList.push_back(no);
	m_activeList.push_back(selectkey);

	selectionList.push_back(no);
	selectionList.push_back(yes);
	selectIter = selectionList.begin();
	timeToChangeScene = 0.f;
	moveKeyLeft = LuaInterface::GetInstance()->getCharValue("moveLeft2");
	moveKeyRight = LuaInterface::GetInstance()->getCharValue("moveRight2");
	moveKeyEnter = LuaInterface::GetInstance()->getCharValue("enterKey");

	keypress = 0.f;
	changedVolume = false;
}

void SceneOptions::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyDown('1'))
		glEnable(GL_CULL_FACE);
	if (KeyboardController::GetInstance()->IsKeyDown('2'))
		glDisable(GL_CULL_FACE);
	if (KeyboardController::GetInstance()->IsKeyDown('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (KeyboardController::GetInstance()->IsKeyDown('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (KeyboardController::GetInstance()->IsKeyDown('5'))
	{
		//Application::GetInstance().m_lockMouse = true;
		//Application::GetInstance().hideMouse(true);
		//SceneManager::GetInstance()->SetActiveScene("Start");
	}
	// For Mouse detection debugging only!
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	std::ostringstream ss;
	float worldX = ((float)mousePosition.x / gameWidth * boundaries.x * 2) - boundaries.x;
	float worldY = ((float)(gameHeight - mousePosition.y) / gameHeight * boundaries.y * 2) - boundaries.y;
	ss << "Mouse: " << worldX << ", " << worldY;
	debuggingMouse->onNotify(ss.str());

	timeToChangeScene += dt;
	keypress += dt;
	if (KeyboardController::GetInstance()->IsKeyDown(moveKeyLeft) && keypress > 0.2f)
	{
		//EntityBase* temp = selectionList.popfront();
		if (selectIter != selectionList.begin())
		{
			--selectIter;
		}
		else
		{
			selectIter = selectionList.end() - 1;
		}
		selectkey->SetPosition((*selectIter)->GetPosition());
		keypress = 0.f;

	}
	else if (KeyboardController::GetInstance()->IsKeyDown(moveKeyRight) && keypress > 0.2f)
	{

		if (selectIter != selectionList.end() - 1)
		{
			++selectIter;
		}
		else
		{
			selectIter = selectionList.begin();
		}
		selectkey->SetPosition((*selectIter)->GetPosition());
		keypress = 0.f;
	}

	if (KeyboardController::GetInstance()->IsKeyDown(moveKeyEnter) && keypress > 0.2f)
	{
		if ((*selectIter) == no)
		{
			changedVolume = true;
			LuaInterface::GetInstance()->saveMusicSettings("volume", 0, true);
			MusicSystem::accessing().musicEngine->setSoundVolume(((float)0) * 0.01f);
			//SceneManager::GetInstance()->quitApp = false;
			//SceneManager::GetInstance()->SetActiveSubScene("Nothing");
		}
		else if ((*selectIter) == yes)
		{
			changedVolume = true;
			LuaInterface::GetInstance()->saveMusicSettings("volume", 100, true);
			MusicSystem::accessing().musicEngine->setSoundVolume(((float)100) * 0.01f);
			//SceneManager::GetInstance()->quitApp = true;
		}

	}

	if (changedVolume)
	{
		changedVolume = false;
		//int volume = LuaInterface::GetInstance()->getMusicVolume("volume");
		//MusicSystem::accessing().musicEngine->setSoundVolume(((float)volume) * 0.01f);
	}
	//if (timeToChangeScene > 2.f)
	//{
	//	float changeTheScale = nyplogo->GetScale().y - dt * 100;
	//	if (changeTheScale < 0.01f)
	//	{
	//		changeTheScale = 0.01f;
	//		//SceneManager::GetInstance()->SetActiveScene("Main");
	//		//nyplogo->SetScale(Vector3(nyplogo->GetScale().x, 100, 0));
	//	}
	//	else
	//	{
	//		nyplogo->SetScale(Vector3(nyplogo->GetScale().x, changeTheScale, 0));
	//	}
	//}
	// For Mouse detection debugging only!
}

void SceneOptions::Render()
{
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->UpdateLightUniforms();
	GraphicsManager::GetInstance()->SetOrthographicProjection(-boundaries.x, boundaries.x, -boundaries.y, boundaries.y, -boundaries.z, boundaries.z);
	GraphicsManager::GetInstance()->AttachCamera(&mainCamera);*/

	for (std::vector<EntityBase*>::iterator it = m_activeList.begin(), end = m_activeList.end(); it != end; ++it)
	{
		(*it)->Render();
	}
}

void SceneOptions::Exit()
{
	GraphicsManager::GetInstance()->DetachCamera();
	selectionList.clear();
	while (m_activeList.size() > 0)
	{
		EntityBase *ex = m_activeList.back();
		if (ex != NULL)
			delete ex;
		m_activeList.pop_back();
	}
	// Delete the lights
	//delete lights[0];
	//delete lights[1];
}