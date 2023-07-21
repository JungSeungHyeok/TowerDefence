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


	SpriteGo* SelectRound = (SpriteGo*)AddGo(new SpriteGo("Ui/SelectRound.png", "Guide Book1"));
	SelectRound->SetOrigin(Origins::MC);
	SelectRound->sortLayer = 100;
	SelectRound->SetPosition(size.x / 2, size.y / 2);

	SelectRound->SetActive(false);

	SpriteGo* guidebackgrund = (SpriteGo*)AddGo(new SpriteGo("Ui/guidebackgrund.png", "Guide Book1"));
	guidebackgrund->SetOrigin(Origins::MC);
	guidebackgrund->sortLayer = 100;
	guidebackgrund->SetPosition(size.x / 2, size.y / 2);

	guidebackgrund->SetActive(false);

	SpriteGo* guidebook1 = (SpriteGo*)AddGo(new SpriteGo("Ui/guidebook1.png", "Guide Book1"));
	guidebook1->SetOrigin(Origins::MC);
	guidebook1->sortLayer = 100;
	guidebook1->SetPosition(size.x / 2, size.y / 2);

	guidebook1->SetActive(false);



	SpriteGo* guidebook2 = (SpriteGo*)AddGo(new SpriteGo("Ui/guidebook2.png", "Guide Book1"));
	guidebook2->SetOrigin(Origins::MC);
	guidebook2->sortLayer = 100;
	guidebook2->SetPosition(size.x / 2, size.y / 2);

	guidebook2->SetActive(false);

	SpriteGo* guidebook3 = (SpriteGo*)AddGo(new SpriteGo("Ui/guidebook3.png", "Guide Book1"));
	guidebook3->SetOrigin(Origins::MC);
	guidebook3->sortLayer = 100;
	guidebook3->SetPosition(size.x / 2, size.y / 2);

	guidebook3->SetActive(false);

	UIButton* startButton = (UIButton*)AddGo(new UIButton("Ui/StartButton.png"));
	startButton->SetOrigin(Origins::MC);
	startButton->sortLayer = 100;
	startButton->SetPosition(size.x /2, size.y * 0.85);

	UIButton* nextButton = (UIButton*)AddGo(new UIButton("Ui/NextButton.png"));
	nextButton->SetOrigin(Origins::MC);
	nextButton->sortLayer = 101;
	nextButton->SetPosition(size.x * 0.612f, size.y * 0.79f);

	nextButton->SetActive(false);
	
	//guidebooks.push_back(guidebook1); //배열에 집어넣고
	guidebooks.push_back(guidebook2);
	guidebooks.push_back(guidebook3);


	sf::Vector2f originalSize = startButton->sprite.getScale();
	sf::Color gammaColor(100, 100, 100, 255);

	startButton->OnEnter = [startButton, originalSize, gammaColor]()
	{

		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/StartButton.png");

		startButton->sprite.setTexture(*tex);
		startButton->sprite.setScale(originalSize * 1.1f);

		startButton->sprite.setColor(gammaColor); // 감마설정
	};

	startButton->OnExit = [startButton, originalSize]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/StartButton.png");
		startButton->sprite.setTexture(*tex);
		startButton->sprite.setScale(originalSize);

		startButton->sprite.setColor(sf::Color::White);  // 감마설정
		
	};

	nextButton->OnEnter = [nextButton, gammaColor]()
	{

		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/nextButton.png");
		nextButton->sprite.setColor(gammaColor); // 감마설정
	};

	

	nextButton->OnExit = [nextButton, gammaColor]()
	{

		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/nextButton.png");
		nextButton->sprite.setColor(sf::Color::White); // 감마설정
	};

	startButton->OnClick = [this, startScene, guidebackgrund, guidebook1, nextButton, startButton]()
	{
		startButton->SetActive(false); // 1
		startScene->SetActive(false); // 2 끄고

		guidebackgrund->SetActive(true); // 3 키고
		guidebook1->SetActive(true); // 4
		nextButton->SetActive(true); // 5
	};

	nextButton->OnClick = [this, nextButton, guidebook2, guidebook3]()
	{
		
		if (ImageIndex == 0)
			guidebook2->SetActive(true);
		else if (ImageIndex == 1)
		{
			sf::Vector2f size = FRAMEWORK.GetWindowSize();
			nextButton->SetPosition(size.x * 0.5f, size.y * 0.79f);
			guidebook3->SetActive(true);
		}
			
		else if (ImageIndex > guidebooks.size() - 1)  // 조건문 추가 인덱스는 0,1,2 / 사이즈는 3이 맞다
		{
			SCENE_MGR.ChangeScene(SceneId::Dev1);

		}

		ImageIndex = (ImageIndex + 1);





		//if (ImageIndex > guidebooks.size())  // 조건문 추가 인덱스는 0,1,2 / 사이즈는 3이 맞다
		//{
		//	SCENE_MGR.ChangeScene(SceneId::Dev1);

		//}








		//guidebooks[ImageIndex]->SetActive(true); // 다음 이미지
		//ImageIndex = (ImageIndex + 1) % (guidebooks.size());


		//if (ImageIndex > guidebooks.size())  // 조건문 추가 인덱스는 0,1,2 / 사이즈는 3이 맞다
		//{
		//	SCENE_MGR.ChangeScene(SceneId::Dev1);

		//}











		//else
		//{
		//	guidebooks[ImageIndex]->SetActive(true); // 다음 이미지
		//	ImageIndex = (ImageIndex + 1) % (guidebooks.size() + 1);
		//}

		/*guidebackgrund->SetActive(true);
		//guidebook1->SetActive(true);*/

		//isguideButton = !isguideButton; // 토글

		//SCENE_MGR.ChangeScene(SceneId::Dev1);
	}; // 넥스트버튼 추가는 했는데 오브젝트 하고 추가

	

	


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



	
	//window.draw(addImage);

}
