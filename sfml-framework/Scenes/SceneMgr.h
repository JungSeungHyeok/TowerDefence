#pragma once
#include "Singleton.h"
#include "Scene.h"

class SceneMgr : public Singleton<SceneMgr>
{
	friend Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	virtual ~SceneMgr() override = default;

	float dtSpeed = 1.0f;

	std::vector<Scene*> scenes;
	SceneId currentSceneId = SceneId::None;
	Scene* currentScene = nullptr;

	SceneId startSceneId = SceneId::Title;

public:
	void Init();
	void Release();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void SetdtSpeed(float speed);

	void ChangeScene(SceneId id);
	Scene* GetCurrScene() const;

};

#define SCENE_MGR (SceneMgr::Instance())
