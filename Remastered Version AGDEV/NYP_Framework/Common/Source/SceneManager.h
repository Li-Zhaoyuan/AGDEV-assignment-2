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

private:
	SceneManager();
	virtual ~SceneManager();

	//std::map<std::string, Scene*> sceneMap;
	std::unordered_map<std::string, Scene*> sceneMap;
	Scene* activeScene/*, *nextScene*/;
    std::vector<Scene*> HistoryOfScenes;
};

#endif // SCENE_MANAGER_H