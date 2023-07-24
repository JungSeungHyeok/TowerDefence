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


	TextGo* startFont = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Start Font"));
	startFont->sortLayer = 101;
	startFont->text.setCharacterSize(40);
	startFont->text.setFillColor(sf::Color::White);
	startFont->text.setString(L"Start"); // �ӽð�
	startFont->SetPosition(size.x / 2 * 0.917f, 584.f);


	UIButton* nextButton = (UIButton*)AddGo(new UIButton("Ui/NextButton.png"));
	nextButton->SetOrigin(Origins::MC);
	nextButton->sortLayer = 101;
	nextButton->SetPosition(size.x * 0.612f, size.y * 0.79f);

	nextButton->SetActive(false);

	UIButton* skipButton = (UIButton*)AddGo(new UIButton("Ui/SkipButton.png"));
	skipButton->SetOrigin(Origins::MC);
	skipButton->sortLayer = 102;
	skipButton->SetPosition(size.x * 0.387f, size.y * 0.79f);

	skipButton->SetActive(false);
	
	//guidebooks.push_back(guidebook1); //�迭�� ����ְ�
	guidebooks.push_back(guidebook2);
	guidebooks.push_back(guidebook3);


	sf::Vector2f originalSize = startButton->sprite.getScale();
	sf::Color gammaColor(100, 100, 100, 255);

	startButton->OnEnter = [startButton, originalSize, gammaColor]()
	{
		// ũ�⼳�� ���� �ӽ�
		//sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/StartButton.png");
		//startButton->sprite.setTexture(*tex); 
		//startButton->sprite.setScale(originalSize * 1.1f);
		
		startButton->sprite.setColor(gammaColor); // ��������
	};

	startButton->OnExit = [startButton, originalSize]()
	{
		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/StartButton.png");
		startButton->sprite.setTexture(*tex);
		startButton->sprite.setScale(originalSize);

		startButton->sprite.setColor(sf::Color::White);  // ��������
		
	};

	skipButton->OnEnter = [skipButton, gammaColor]()
	{

		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/SkipButton.png");
		skipButton->sprite.setColor(gammaColor); // ��������
	};

	nextButton->OnEnter = [nextButton, gammaColor]()
	{

		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/NextButton.png");
		nextButton->sprite.setColor(gammaColor); // ��������
	};
	

	nextButton->OnExit = [nextButton, gammaColor]()
	{

		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/NextButton.png");
		nextButton->sprite.setColor(sf::Color::White); // ��������
	};

	skipButton->OnExit = [skipButton, gammaColor]()
	{

		sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/SkipButton.png");
		skipButton->sprite.setColor(sf::Color::White); // ��������
	};

	startButton->OnClick = [this, startScene, startFont, guidebackgrund, guidebook1, nextButton, startButton, skipButton]()
	{
		startButton->SetActive(false); // 1
		startScene->SetActive(false); // 2
		startFont->SetActive(false); // 3 ����

		guidebackgrund->SetActive(true); // 1 Ű��
		guidebook1->SetActive(true); // 2
		nextButton->SetActive(true); // 3
		skipButton->SetActive(true); // 4
	};

	nextButton->OnClick = [this, nextButton, guidebook2, guidebook3, skipButton]()
	{
		
		if (ImageIndex == 0)
			guidebook2->SetActive(true);
		else if (ImageIndex == 1)
		{
			sf::Vector2f size = FRAMEWORK.GetWindowSize();
			nextButton->SetPosition(size.x * 0.5f, size.y * 0.79f);
			guidebook3->SetActive(true);
			skipButton->SetActive(false);
		}
			
		else if (ImageIndex > guidebooks.size() - 1)  // ���ǹ� �߰� �ε����� 0,1,2 / ������� 3�� �´�
		{
			SCENE_MGR.ChangeScene(SceneId::Dev1);
		}

		ImageIndex = (ImageIndex + 1);
	}; 

	skipButton->OnClick = [skipButton]()
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



	
	//window.draw(addImage);

}
