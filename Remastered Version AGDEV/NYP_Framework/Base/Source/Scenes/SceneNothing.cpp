#include "SceneNothing.h"
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

SceneNothing *SceneNothing::cantTouchMain = new SceneNothing(SceneManager::GetInstance());

SceneNothing::SceneNothing(SceneManager *zeSceneManager)
{
	Scene_name_ = "Nothing";
	zeSceneManager->AddSubScene(Scene_name_, this);
}

SceneNothing::~SceneNothing()
{
}

void SceneNothing::Init()
{
	

	// Tell the graphics manager to use the shader we just loaded
	GraphicsManager::GetInstance()->SetActiveShader("default");

	mainCamera.Init(Vector3(0, 0, 9.95f), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//m_activeList.push_back(Create::Entity("reference", Vector3(0, 0, 0)));

	boundaries.Set(400, 300, 10);   // We will just take the resolution of 800 by 600

	m_activeList.push_back(Create::Text2DObject("text", Vector3(-boundaries.x, -boundaries.y + 50, 0), "Press Space To Start", Vector3(25, 25, 1), Color(0, 1, 0)));
	debuggingMouse = Create::Text2DObject("text", Vector3(-boundaries.x, -boundaries.y + 75, 0), "Mouse", Vector3(25, 25, 1), Color(0, 1, 0));
	m_activeList.push_back(debuggingMouse);

	gameWidth = Application::GetInstance().GetWindowWidth();
	gameHeight = Application::GetInstance().GetWindowHeight();
	//Application::GetInstance().hideMouse(false);
	//	GenericEntity* test = Create::Entity(,,)
	float worldX = ((float)(gameWidth / 2) / gameWidth * boundaries.x * 2) - boundaries.x;
	float worldY = ((float)(gameHeight - (gameHeight/2)) / gameHeight * boundaries.y * 2) - boundaries.y;
	//nyplogo = Create::Entity("LOGO", Vector3(worldX, worldY, 0.f), Vector3(gameWidth*0.1 * (360 / 77), gameWidth*0.1, 5));
	//m_activeList.push_back(nyplogo);
	timeToChangeScene = 0.f;
}

void SceneNothing::Update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyDown('1'))
		glEnable(GL_CULL_FACE);
	if (KeyboardController::GetInstance()->IsKeyDown('2'))
		glDisable(GL_CULL_FACE);
	if (KeyboardController::GetInstance()->IsKeyDown('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (KeyboardController::GetInstance()->IsKeyDown('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*if (KeyboardController::GetInstance()->IsKeyDown('5'))
	{
		Application::GetInstance().m_lockMouse = true;
		Application::GetInstance().hideMouse(true);
		SceneManager::GetInstance()->SetActiveScene("Main");
	}*/
	// For Mouse detection debugging only!
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	std::ostringstream ss;
	float worldX = ((float)mousePosition.x / gameWidth * boundaries.x * 2) - boundaries.x;
	float worldY = ((float)(gameHeight - mousePosition.y) / gameHeight * boundaries.y * 2) - boundaries.y;
	ss << "Mouse: " << worldX << ", " << worldY;
	debuggingMouse->onNotify(ss.str());

	//timeToChangeScene += dt;
	//if (timeToChangeScene > 2.f)
	//{
	//	float changeTheScale = nyplogo->GetScale().y - dt * 100;
	//	if (changeTheScale < 0.01f)
	//	{
	//		changeTheScale = 0.01f;
	//		SceneManager::GetInstance()->SetActiveScene("Main");
	//		//nyplogo->SetScale(Vector3(nyplogo->GetScale().x, 100, 0));
	//	}
	//	else
	//	{
	//		nyplogo->SetScale(Vector3(nyplogo->GetScale().x, changeTheScale, 0));
	//	}
	//}
	// For Mouse detection debugging only!
}

void SceneNothing::Render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GraphicsManager::GetInstance()->UpdateLightUniforms();
	//GraphicsManager::GetInstance()->SetOrthographicProjection(-boundaries.x, boundaries.x, -boundaries.y, boundaries.y, -boundaries.z, boundaries.z);
	//GraphicsManager::GetInstance()->AttachCamera(&mainCamera);

	//for (std::vector<EntityBase*>::iterator it = m_activeList.begin(), end = m_activeList.end(); it != end; ++it)
	//{
	//	//(*it)->Render();
	//}
}

void SceneNothing::Exit()
{
	GraphicsManager::GetInstance()->DetachCamera();
	// Delete the lights
	//delete lights[0];
	//delete lights[1];
}