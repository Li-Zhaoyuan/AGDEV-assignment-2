#include "Application.h"
#include "MouseController.h"
#include "KeyboardController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#include "MeshBuilder.h"
#include "LoadTGA.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneText.h"
#include "EntityManager.h"
#include "MusicsStuff\MusicSystem.h"
#include "../lua/LuaInterface.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}
//lua_State*l;
static int CreateOBJ(lua_State*l)
{
	int n = lua_gettop(l);// how many parameters :V

	/*for (int i = 1; i < n; ++i)
	{

	}*/
	//MeshBuilder::GetInstance()->GenerateOBJ("ASTEROID", "OBJ//asteroid.obj")->textureID = LoadTGA("Image//lasergun.tga");
	//std::string type = lua_tostring(l, 1);
	std::string meshName = lua_tostring(l,1);
	std::string filepathForOBJ = lua_tostring(l, 2);
	std::string filepathForText = lua_tostring(l, 3);
	
	Mesh* tempobj;
	
	tempobj = MeshBuilder::GetInstance()->GenerateOBJ(meshName, filepathForOBJ);
	tempobj->textureID = LoadTGA(filepathForText.c_str());
	
	return 1;
}

static int CreateQuad(lua_State*l)
{
	int n = lua_gettop(l);// how many parameters :V

	/*for (int i = 1; i < n; ++i)
	{

	}*/
	//MeshBuilder::GetInstance()->GenerateOBJ("ASTEROID", "OBJ//asteroid.obj")->textureID = LoadTGA("Image//lasergun.tga");
	//std::string type = lua_tostring(l, 1);
	std::string meshName = lua_tostring(l, 1);
	//std::string filepathForOBJ = lua_tostring(l, 2);
	std::string filepathForText = lua_tostring(l, 2);

	Mesh* tempobj;

	tempobj = MeshBuilder::GetInstance()->GenerateQuad(meshName, Color(1, 1, 1), 1.f);
	tempobj->textureID = LoadTGA(filepathForText.c_str());

	return 1;
}

static int CreateText(lua_State*l)
{
	int n = lua_gettop(l);// how many parameters :V

	/*for (int i = 1; i < n; ++i)
	{

	}*/
	//MeshBuilder::GetInstance()->GenerateOBJ("ASTEROID", "OBJ//asteroid.obj")->textureID = LoadTGA("Image//lasergun.tga");
	//std::string type = lua_tostring(l, 1);
	std::string meshName = lua_tostring(l, 1);
	//std::string filepathForOBJ = lua_tostring(l, 2);
	int row = lua_tointeger(l, 2);
	int col = lua_tointeger(l, 3);
	std::string filepathForText = lua_tostring(l, 4);

	Mesh* tempobj;

	tempobj = MeshBuilder::GetInstance()->GenerateText(meshName, row, col);
	tempobj->textureID = LoadTGA(filepathForText.c_str());

	return 1;
}

static int CreateAxis(lua_State*l)
{
	int n = lua_gettop(l);// how many parameters :V

	/*for (int i = 1; i < n; ++i)
	{

	}*/
	//MeshBuilder::GetInstance()->GenerateOBJ("ASTEROID", "OBJ//asteroid.obj")->textureID = LoadTGA("Image//lasergun.tga");
	//std::string type = lua_tostring(l, 1);
	std::string meshName = lua_tostring(l, 1);
	//std::string filepathForOBJ = lua_tostring(l, 2);
	//std::string filepathForText = lua_tostring(l, 2);

	Mesh* tempobj;

	tempobj = MeshBuilder::GetInstance()->GenerateAxes(meshName);
	//tempobj->textureID = LoadTGA(filepathForText.c_str());

	return 1;
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//Create a window and create its OpenGL context
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());	//Obtain Width and Height values from the monitor;
    m_window_height = mode->height;
    m_window_width = mode->width;
    
    m_window = glfwCreateWindow(m_window_width, m_window_height, "Mah Physicz", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	// Hide the cursor
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetMouseButtonCallback(m_window, &Application::MouseButtonCallbacks);
	glfwSetScrollCallback(m_window, &Application::MouseScrollCallbacks);

	// Init systems
	GraphicsManager::GetInstance()->Init();
    // Load all the meshes
   // MeshBuilder::GetInstance()->GenerateAxes("reference");
    //MeshBuilder::GetInstance()->GenerateCrossHair("crosshair");
    //MeshBuilder::GetInstance()->GenerateQuad("quad", Color(0, 0, 0), 1.f);
   // MeshBuilder::GetInstance()->GetMesh("quad")->textureID = LoadTGA("Image//calibri.tga");
    //MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
    //MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
    //MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
    //MeshBuilder::GetInstance()->GenerateOBJ("Chair", "OBJ//chair.obj");
    //MeshBuilder::GetInstance()->GetMesh("Chair")->textureID = LoadTGA("Image//chair.tga");
    /*MeshBuilder::GetInstance()->GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
    MeshBuilder::GetInstance()->GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);
    MeshBuilder::GetInstance()->GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 1.f);
    MeshBuilder::GetInstance()->GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
    MeshBuilder::GetInstance()->GenerateCube("cube", Color(1.0f, 1.0f, 0.0f), 1.0f);
    MeshBuilder::GetInstance()->GetMesh("cone")->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
    MeshBuilder::GetInstance()->GetMesh("cone")->material.kSpecular.Set(0.f, 0.f, 0.f);*/

    //MeshBuilder::GetInstance()->GenerateOBJ("ANDROID", "OBJ//android2.obj")->textureID = LoadTGA("Image//android2.tga");    // creating the basic NPC

    Mesh *zeMesh = MeshBuilder::GetInstance()->GenerateQuadXZ("GRIDMESH", Color(1, 1, 1), 1.f);
    zeMesh->mode = Mesh::DRAW_LINES;

    MusicSystem::accessing().Init();
    MusicSystem::accessing().playBackgroundMusic("BGM");

    LuaInterface::GetInstance()->Init();
   /* LuaInterface::GetInstance()->saveFloatValue("Score1 =", 800.10f);
    LuaInterface::GetInstance()->saveIntValue("Score2 =", 100);*/

	LuaInterface::GetInstance()->theLuaForMeshs = lua_open();
	luaL_openlibs(LuaInterface::GetInstance()->theLuaForMeshs);
	
	lua_register(LuaInterface::GetInstance()->theLuaForMeshs, "CreateOBJ", CreateOBJ);
	lua_register(LuaInterface::GetInstance()->theLuaForMeshs, "CreateQuad", CreateQuad);
	lua_register(LuaInterface::GetInstance()->theLuaForMeshs, "CreateText", CreateText);
	lua_register(LuaInterface::GetInstance()->theLuaForMeshs, "CreateAxis", CreateAxis);

	luaL_dofile(LuaInterface::GetInstance()->theLuaForMeshs, "lua//createmesh.lua");
	lua_close(LuaInterface::GetInstance()->theLuaForMeshs);

    lua_getglobal(LuaInterface::GetInstance()->theLuaState, "Waypoint_A_1");
    Vector3 testingDebugWaypoint1(LuaInterface::GetInstance()->getField("x"), LuaInterface::GetInstance()->getField("y"), LuaInterface::GetInstance()->getField("z"));
    std::cout << "Wapoint 1: " << testingDebugWaypoint1 << std::endl;
    m_lockMouse = false;
}

void Application::Run()
{
	SceneManager::GetInstance()->SetActiveScene("Main");
	SceneManager::GetInstance()->SetActiveSubScene("HighScore");
    // Active Window Detection
    HWND hwnd = GetActiveWindow();
    UpdateInput();
    PostInputUpdate();
    m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		glfwPollEvents();
        if (hwnd == GetActiveWindow())
        {
            UpdateInput();

            SceneManager::GetInstance()->Update(m_timer.getElapsedTime());
            SceneManager::GetInstance()->Render();
		    PostInputUpdate();
        }

		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...

        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   
		
	}
	SceneManager::GetInstance()->Exit();
    SceneManager::GetInstance()->Destroy();
    EntityManager::GetInstance()->Destroy();
    GraphicsManager::GetInstance()->Destroy();
    LuaInterface::GetInstance()->Destroy();
    MeshBuilder::GetInstance()->Destroy();
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
    _CrtDumpMemoryLeaks();
}

void Application::UpdateInput()
{
	// Update Mouse Position
#ifdef _DEBUG
    POINT mousePosition;
    GetCursorPos(&mousePosition);

    MouseController::GetInstance()->UpdateMousePosition(-mousePosition.x, -mousePosition.y);
#else
    double mouse_currX, mouse_currY;
    glfwGetCursorPos(m_window, &mouse_currX, &mouse_currY);
    MouseController::GetInstance()->UpdateMousePosition(-mouse_currX, -mouse_currY);
#endif
	//double mouse_currX, mouse_currY;
	//glfwGetCursorPos(m_window, &mouse_currX, &mouse_currY);

	// Update Keyboard Input
	for (int i = 0; i < KeyboardController::MAX_KEYS; ++i)
		KeyboardController::GetInstance()->UpdateKeyboardStatus(i, IsKeyPressed(i));
}

void Application::PostInputUpdate()
{
	// If mouse is centered, need to update the center position for next frame
	if (MouseController::GetInstance()->GetKeepMouseCentered())
	{
#ifdef _DEBUG

        if (m_lockMouse)
        {
            POINT mousePosition;
            GetCursorPos(&mousePosition);

            MouseController::GetInstance()->UpdateMousePosition(-mousePosition.x, -mousePosition.y);
            SetCursorPos(m_window_width / 2, m_window_height / 2);
        }
#else
        double mouse_currX, mouse_currY;
        mouse_currX = m_window_width >> 1;
        mouse_currY = m_window_height >> 1;
        glfwSetCursorPos(m_window, mouse_currX, mouse_currY);
#endif
	}

	// Call input systems to update at end of frame
	MouseController::GetInstance()->EndFrameUpdate();
	KeyboardController::GetInstance()->EndFrameUpdate();
}

void Application::MouseButtonCallbacks(GLFWwindow* window, int button, int action, int mods)
{
	// Send the callback to the mouse controller to handle
	if (action == GLFW_PRESS)
		MouseController::GetInstance()->UpdateMouseButtonPressed(button);
	else
		MouseController::GetInstance()->UpdateMouseButtonReleased(button);
}

void Application::MouseScrollCallbacks(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseController::GetInstance()->UpdateMouseScroll(xoffset, yoffset);
}

int Application::GetWindowHeight()
{
	return m_window_height;
}

int Application::GetWindowWidth()
{
	return m_window_width;
}

void Application::hideMouse(const bool &zeToggle)
{
    switch (zeToggle)
    {
    case true:
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        break;
    default:
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

