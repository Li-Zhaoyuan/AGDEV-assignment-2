#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
//#include <map>
#include <string>
#include "Scene.h"
#include <unordered_map>

class Scene;

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;
public:
	// System Interface
	void Update(double _dt);
	void Render();
	void Exit();

	// User Interface
	void AddScene(const std::string& _name, Scene* _scene);
	void RemoveScene(const std::string& _name);
	void SetActiveScene(const std::string& _name);
	bool CheckSceneExist(const std::string& _name);
    //bool NotifyCurrScene(const std::string &zeEvent) { activeScene->}
    Scene *GetCurrScene() { return activeScene; }
    bool TransitPreviousScene();

	// User Interface

	void UpdateSub(double _dt);
	void RenderSub();
	void AddSubScene(const std::string& _name, Scene* _scene);
	void RemoveSubScene(const std::string& _name);
	void SetActiveSubScene(const std::string& _name);
	bool CheckSubSceneExist(const std::string& _name);
	//bool NotifyCurrScene(const std::string &zeEvent) { activeScene->}
	Scene *GetCurrSubScene() { return activeSubScene; }
	bool TransitPreviousSubScene();

	bool quitApp;

private:
	SceneManager();
	virtual ~SceneManager();

	//std::map<std::string, Scene*> sceneMap;
	std::unordered_map<std::string, Scene*> sceneMap;
	Scene* activeScene/*, *nextScene*/;
    std::vector<Scene*> HistoryOfScenes;

	std::unordered_map<std::string, Scene*> subsceneMap;
	Scene* activeSubScene/*, *nextScene*/;
	std::vector<Scene*> HistoryOfSubScenes;
};

#endif // SCENE_MANAGER_H