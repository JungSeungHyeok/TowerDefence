#include "stdafx.h"
#include "SceneTitle.h"
#include "TextGo.h"


SceneTitle::SceneTitle() : Scene(SceneId::Dev2)
{
	resourceListPath = "scripts/DefaultResourceList.csv";
	//	resourceListPath = "scripts/SceneDev2ResourceList.csv";
}

void SceneTitle::Init()
{
	Release();
	sf::Vector2f size = FRAMEWORK.GetWindowSize();

	SpriteGo* startScene = (SpriteGo*)AddGo(new SpriteGo("Ui/StartScene.png", "Start Scene"));

	startScene->SetOrigin(Origins::MC);
	startScene->sortLayer = 100;
	startScene->SetPosition(size.x / 2, size.y / 2);

	/*tileMap = (TileMap*)AddGo(new TileMap("graphics/grass.png", "Tile Map"));

	UIButton* button = (UIButton*)AddGo(new UIButton("Ui/StartButton.png"));*/

	UIButton* button = (UIButton*)AddGo(new UIButton("Ui/StartButton.png"));
	button->SetOrigin(Origins::MC);
	button->sortLayer = 100;
	button->SetPosition(size.x /2, size.y * 0.85);
	
	sf::Vector2f originalSize = button->sprite.getScale();

	button->OnEnter = [button, originalSize]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/StartButton.png");
		button->sprite.setTexture(*tex);
		button->sprite.setScale(originalSize * 1.1f);
		
	};
	button->OnExit = [button, originalSize]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/StartButton.png");
		button->sprite.setTexture(*tex);
		button->sprite.setScale(originalSize);
	};
	button->OnClick = [this]()
	{
		SCENE_MGR.ChangeScene(SceneId::Dev1);
	};


	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneTitle::Enter()
{
	Scene::Enter();

	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter({ 0,0 });

	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneId::Dev1);
	}*/
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
