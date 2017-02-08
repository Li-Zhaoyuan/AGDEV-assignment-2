#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() : activeScene(nullptr), activeSubScene(nullptr)/*, nextScene(nullptr)*/
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(double _dt)
{
	// Check for change of scene
	//if (nextScene != activeScene)
    if (HistoryOfScenes.back() != activeScene)
	{
		if (activeScene)
		{
			// Scene is valid, need to call appropriate function to exit
			activeScene->Exit();
		}
		
		//activeScene = nextScene;
        activeScene = HistoryOfScenes.back();
		activeScene->Init();
	}

	if (activeScene)
		activeScene->Update(_dt);
}

void SceneManager::Render()
{
	if (activeScene)
		activeScene->Render();
}
//
//void SceneManager::Exit()
//{
//	// Delete all scenes stored and empty the entire map
//	activeScene->Exit();
//	activeScene = nullptr;
//	std::unordered_map<std::string, Scene*>::iterator it, end;
//	end = sceneMap.end();
//	for (it = sceneMap.begin(); it != end; ++it)
//	{
//		delete it->second;
//	}
//	sceneMap.clear();
//}

void SceneManager::AddScene(const std::string& _name, Scene* _scene)
{
	if (CheckSceneExist(_name))
	{
		// Scene Exist, unable to proceed
		throw std::exception("Duplicate scene name provided");
	}

	if (_scene == nullptr)
	{
		throw std::invalid_argument("Invalid scene pointer");
	}

	// Nothing wrong, add the scene to our map
	sceneMap[_name] = _scene;
}

void SceneManager::RemoveScene(const std::string& _name)
{
	// Does nothing if it does not exist
	if (!CheckSceneExist(_name))
		return;

	Scene* target = sceneMap[_name];
	if (target == activeScene || /*target == nextScene*/HistoryOfScenes.back() == target)
	{
		throw std::exception("Unable to remove active/next scene");
	}

	// Delete and remove from our map
	delete target;
	sceneMap.erase(_name);
}

void SceneManager::SetActiveScene(const std::string& _name)
{
	if (!CheckSceneExist(_name))
	{
		// Scene does not exist
		throw std::exception("Scene does not exist");
	}

	// Scene exist, set the next scene pointer to that scene
	//nextScene = sceneMap[_name];
    HistoryOfScenes.push_back(sceneMap[_name]);
}

bool SceneManager::CheckSceneExist(const std::string& _name)
{
	return sceneMap.count(_name) != 0;
}

bool SceneManager::TransitPreviousScene()
{
    if (HistoryOfScenes.size() > 1)
    {
        HistoryOfScenes.pop_back();
        SetActiveScene(HistoryOfScenes.back()->Scene_name_);
        return true;
    }
    return false;
}

void SceneManager::UpdateSub(double _dt)
{
	// Check for change of scene
	//if (nextScene != activeScene)
	if (HistoryOfSubScenes.back() != activeSubScene)
	{
		if (activeSubScene)
		{
			// Scene is valid, need to call appropriate function to exit
			activeSubScene->Exit();
		}

		//activeScene = nextScene;
		activeSubScene = HistoryOfSubScenes.back();
		activeSubScene->Init();
	}

	if (activeSubScene)
		activeSubScene->Update(_dt);
}

void SceneManager::RenderSub()
{
	if (activeSubScene)
		activeSubScene->Render();
}

void SceneManager::Exit()
{
	// Delete all scenes stored and empty the entire map
	activeScene->Exit();
	activeScene = nullptr;
	if (activeSubScene != NULL)
		activeSubScene->Exit();
	activeSubScene = nullptr;
	std::unordered_map<std::string, Scene*>::iterator it, end, it2, end2;
	end = sceneMap.end();
	end2 = subsceneMap.end();
	for (it = sceneMap.begin(); it != end; ++it)
	{
		delete it->second;
	}
	for (it2 = subsceneMap.begin(); it2 != end2; ++it2)
	{
		delete it2->second;
	}
	sceneMap.clear();
	subsceneMap.clear();
}

void SceneManager::AddSubScene(const std::string& _name, Scene* _scene)
{
	if (CheckSubSceneExist(_name))
	{
		// Scene Exist, unable to proceed
		throw std::exception("Duplicate scene name provided");
	}

	if (_scene == nullptr)
	{
		throw std::invalid_argument("Invalid scene pointer");
	}

	// Nothing wrong, add the scene to our map
	subsceneMap[_name] = _scene;
}

void SceneManager::RemoveSubScene(const std::string& _name)
{
	// Does nothing if it does not exist
	if (!CheckSubSceneExist(_name))
		return;

	Scene* target = subsceneMap[_name];
	if (target == activeSubScene || /*target == nextScene*/HistoryOfSubScenes.back() == target)
	{
		throw std::exception("Unable to remove active/next scene");
	}

	// Delete and remove from our map
	delete target;
	subsceneMap.erase(_name);
}

void SceneManager::SetActiveSubScene(const std::string& _name)
{
	if (!CheckSubSceneExist(_name))
	{
		// Scene does not exist
		throw std::exception("Scene does not exist");
	}

	// Scene exist, set the next scene pointer to that scene
	//nextScene = sceneMap[_name];
	HistoryOfSubScenes.push_back(subsceneMap[_name]);
}

bool SceneManager::CheckSubSceneExist(const std::string& _name)
{
	return subsceneMap.count(_name) != 0;
}

bool SceneManager::TransitPreviousSubScene()
{
	if (HistoryOfSubScenes.size() > 1)
	{
		HistoryOfSubScenes.pop_back();
		SetActiveSubScene(HistoryOfSubScenes.back()->Scene_name_);
		return true;
	}
	return false;
}