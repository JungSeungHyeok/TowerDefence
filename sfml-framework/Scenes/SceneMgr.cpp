#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h" // ���� ���� �÷��� ��
#include "SceneDev2.h" // ���� ��ŸƮ ������ ����
#include "SceneTitle.h"

// #include "SceneStart.h" // ���� ����Ʈ ��
// #include "SceneRoundSelect.h"
// #include "ScenePause.h" // ���� ��


void SceneMgr::Init()
{
	if (!scenes.empty())
	{
		Release();
	}


	scenes.push_back(new SceneDev1());
	scenes.push_back(new SceneDev2());
	scenes.push_back(new SceneTitle());
	
	
	// Ÿ�� ���� ��
	// ��� ui��

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentSceneId = startSceneId;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();


}

void SceneMgr::Release()
{
	if (scenes.empty())
	{
		return;
	}

	for (auto scene : scenes)
	{
		//scene->Release();
		delete scene;
	}
	scenes.clear();

	currentSceneId = SceneId::None;
	currentScene = nullptr;
}

void SceneMgr::Update(float dt)
{
	currentScene->Update(dt * dtSpeed);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	currentScene->Draw(window);
}

void SceneMgr::SetdtSpeed(float speed)
{
	dtSpeed = speed;
}

void SceneMgr::ChangeScene(SceneId id)
{
	currentScene->Exit();
	currentSceneId = id;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
}

Scene* SceneMgr::GetCurrScene() const
{
	return currentScene;
}
