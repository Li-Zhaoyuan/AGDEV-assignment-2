#include "SceneMain.h"
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

SceneMain *SceneMain::cantTouchMain = new SceneMain(SceneManager::GetInstance());

SceneMain::SceneMain(SceneManager *zeSceneManager)
{
    Scene_name_ = "Main";
    zeSceneManager->AddScene(Scene_name_, this);
	moveKeyUp = 'W';
	moveKeyDown = 'S';
	moveKeyEnter = (char)13;
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
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

    m_activeList.push_back(Create::Entity("reference", Vector3(0, 0, 0)));

    boundaries.Set(400, 300, 10);   // We will just take the resolution of 800 by 600

    m_activeList.push_back(Create::Text2DObject("text", Vector3(-boundaries.x, -boundaries.y + 50, 0), "Press Space To Start", Vector3(25, 25, 1), Color(0, 1, 0)));
    debuggingMouse = Create::Text2DObject("text", Vector3(-boundaries.x, -boundaries.y + 75, 0), "Mouse", Vector3(25, 25, 1), Color(0, 1, 0));
    m_activeList.push_back(debuggingMouse);

    gameWidth = Application::GetInstance().GetWindowWidth();
    gameHeight = Application::GetInstance().GetWindowHeight();
    Application::GetInstance().hideMouse(false);

	float titleX = ((float)(gameWidth / 2) / gameWidth * boundaries.x * 2) - boundaries.x;
	float titleY = ((float)(gameHeight - (gameHeight * 0.2f)) / gameHeight * boundaries.y * 2) - boundaries.y;

	float startX = ((float)(gameWidth / 4) / gameWidth * boundaries.x * 2) - boundaries.x;
	float startY = ((float)(gameHeight - (gameHeight * 0.4f)) / gameHeight * boundaries.y * 2) - boundaries.y;

	float highscoreX = ((float)(gameWidth / 4) / gameWidth * boundaries.x * 2) - boundaries.x;
	float highscoreY = ((float)(gameHeight - (gameHeight * 0.6f)) / gameHeight * boundaries.y * 2) - boundaries.y;

	float quitX = ((float)(gameWidth / 4) / gameWidth * boundaries.x * 2) - boundaries.x;
	float quitY = ((float)(gameHeight - (gameHeight * 0.8f)) / gameHeight * boundaries.y * 2) - boundaries.y;

	float selectX = ((float)(gameWidth / 4) / gameWidth * boundaries.x * 2) - boundaries.x;
	float selectY = ((float)(gameHeight - (gameHeight * 0.4f)) / gameHeight * boundaries.y * 2) - boundaries.y;

	title = Create::Entity("GAMETITLE", Vector3(titleX, titleY, 0.f), Vector3(gameWidth*0.04 * (145 / 17), gameWidth*0.04, 5));
	startbutton = Create::Entity("STARTBUTTON", Vector3(startX, startY, 0.f), Vector3(gameWidth*0.02 * (800/199), gameWidth*0.02, 5));
	highscorebutton = Create::Entity("HIGHSCORE", Vector3(highscoreX, highscoreY, 0.f), Vector3(gameWidth*0.02 * (800 / 199), gameWidth*0.02, 5));
	quitbutton = Create::Entity("QUITBUTTON", Vector3(quitX, quitY, 0.f), Vector3(gameWidth*0.02 * (800 / 199), gameWidth*0.02, 5));
	selectkey = Create::Entity("SELECT", Vector3(startX, startY, 0.f), Vector3((gameWidth*0.02 * (800 / 199))*1.2f, (gameWidth*0.02)*1.2f, 5));
	m_activeList.push_back(title);
	m_activeList.push_back(startbutton);
	m_activeList.push_back(highscorebutton);
	m_activeList.push_back(quitbutton);
	m_activeList.push_back(selectkey);
	selectionList.push_back(startbutton);
	selectionList.push_back(highscorebutton);
	selectionList.push_back(quitbutton);
	selectIter = selectionList.begin();
	keypress = 1.f;
	showSubScene = false;
	titleScale = 0.f;
	
	moveKeyUp = LuaInterface::GetInstance()->getCharValue("moveUp");
	moveKeyDown = LuaInterface::GetInstance()->getCharValue("moveDown");
	moveKeyEnter = LuaInterface::GetInstance()->getCharValue("enterKey");
	/*startbutton;
	highscorebutton;
	quitbutton;
	selectkey;*/
//	GenericEntity* test = Create::Entity(,,)
}

void SceneMain::Update(double dt)
{
    if (KeyboardController::GetInstance()->IsKeyDown('1'))
        glEnable(GL_CULL_FACE);
    if (KeyboardController::GetInstance()->IsKeyDown('2'))
        glDisable(GL_CULL_FACE);
    if (KeyboardController::GetInstance()->IsKeyDown('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (KeyboardController::GetInstance()->IsKeyDown('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (KeyboardController::GetInstance()->IsKeyDown(' '))
    {
        Application::GetInstance().m_lockMouse = true;
        Application::GetInstance().hideMouse(true);
        SceneManager::GetInstance()->SetActiveScene("Start");
    }
	keypress += dt;
	if (KeyboardController::GetInstance()->IsKeyDown(moveKeyUp) && keypress > 0.2f)
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
	else if (KeyboardController::GetInstance()->IsKeyDown(moveKeyDown) && keypress > 0.2f)
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
		if ((*selectIter) == startbutton)
		{
			Application::GetInstance().m_lockMouse = true;
			Application::GetInstance().hideMouse(true);
			SceneManager::GetInstance()->SetActiveScene("Start");
		}
		else if ((*selectIter) == highscorebutton)
		{
			SceneManager::GetInstance()->SetActiveSubScene("HighScore");
			showSubScene = true;
		}
		else if ((*selectIter) == quitbutton)
		{
			SceneManager::GetInstance()->SetActiveSubScene("Quit");
			showSubScene = true;
		}

	}

	static float f = 1;

	if (f*titleScale < 2)
	{
		titleScale += 10 * dt * f;
	}
	else
	{
		f = -f;
	}

	float scaleX = title->GetScale().x;
	float scaleY = title->GetScale().y;
	title->SetScale(Vector3(scaleX + titleScale, scaleY + titleScale, 1));

    // For Mouse detection debugging only!
    POINT mousePosition;
    GetCursorPos(&mousePosition);
    std::ostringstream ss;
    float worldX = ((float)mousePosition.x / gameWidth * boundaries.x * 2) - boundaries.x;
    float worldY = ((float)(gameHeight - mousePosition.y) / gameHeight * boundaries.y * 2) - boundaries.y;
    ss << "Mouse: " << worldX << ", " << worldY;
    debuggingMouse->onNotify(ss.str());
    // For Mouse detection debugging only!

	if (showSubScene)
		SceneManager::GetInstance()->UpdateSub(dt);
}

void SceneMain::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //GraphicsManager::GetInstance()->UpdateLightUniforms();
    GraphicsManager::GetInstance()->SetOrthographicProjection(-boundaries.x, boundaries.x, -boundaries.y, boundaries.y, -boundaries.z, boundaries.z);
    GraphicsManager::GetInstance()->AttachCamera(&mainCamera);

    for (std::vector<EntityBase*>::iterator it = m_activeList.begin(), end = m_activeList.end(); it != end; ++it)
    {
        (*it)->Render();
    }
	if (showSubScene)
		SceneManager::GetInstance()->RenderSub();
}

void SceneMain::Exit()
{
    GraphicsManager::GetInstance()->DetachCamera();
    // Delete the lights
    //delete lights[0];
    //delete lights[1];
}