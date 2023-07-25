#include "stdafx.h"
#include "SceneDev1.h"

#include "TileMap.h"

#include "InputMgr.h"

#include "SoundGo.h"
#include "SpriteEffect.h"

#include "Enemy.h"
#include "Tower.h"
#include "Arrow.h"
#include "SceneMgr.h"
#include <thread>
#include <chrono>


SceneDev1::SceneDev1() : Scene(SceneId::Dev1), tower(nullptr)
{
	resourceListPath = "scripts/SceneDev1ResourceList.csv";
}

void SceneDev1::Init()
{
	Release();

	sf::Vector2f size = FRAMEWORK.GetWindowSize();

	// 백그라운드
	SpriteGo* background = (SpriteGo*)AddGo(new SpriteGo("Ui/guidebackgrund.png", "Back Ground"));
	background->SetOrigin(Origins::MC);
	background->sortLayer = 1;
	background->SetPosition(size.x / 2, size.y / 2);

	// 스타트 버튼 움직이게
	roundStart = (SpriteGo*)AddGo(new SpriteGo("Ui/roundStart.png", "Round Start"));
	roundStart->SetOrigin(Origins::MC);
	roundStart->sortLayer = 2;
	roundStart->SetPosition(size.x / 2, size.y / 2);
	
	UIButton* startButton = (UIButton*)AddGo(new UIButton("Ui/roundStart.png", "Pause Button"));
	startButton->SetOrigin(Origins::MC);
	startButton->sortLayer = 100;
	startButton->SetPosition({ 1241, 33 });

	// 퍼즈 버튼
	UIButton* pauseButton = (UIButton*)AddGo(new UIButton("Ui/pauseButton.png", "Pause Button"));
	pauseButton->SetOrigin(Origins::MC);
	pauseButton->sortLayer = 100;
	pauseButton->SetPosition({ 1241, 96 });

	// 볼륨 On
	UIButton* volumeOnButton = (UIButton*)AddGo(new UIButton("Ui/volumeOnButton.png", "Volume On Button"));
	volumeOnButton->SetOrigin(Origins::MC);
	volumeOnButton->sortLayer = 100;
	volumeOnButton->SetPosition({ 1241, 156 });

	// 볼륨 Off
	UIButton* volumeOffButton = (UIButton*)AddGo(new UIButton("Ui/volumeOffButton.png", "Volume Off Button"));
	volumeOffButton->SetOrigin(Origins::MC);
	volumeOffButton->sortLayer = 100;
	volumeOffButton->SetPosition({ 1241, 156 });
	//volumeOffButton->SetPosition({ 1241, 222 });
	bool volumeOnOff = true;

	// 컨티뉴 버튼
	UIButton* continueButton = (UIButton*)AddGo(new UIButton("Ui/continueButton.png", "Volume Off Button"));
	continueButton->SetOrigin(Origins::MC);
	continueButton->sortLayer = 101;
	continueButton->SetPosition({ 470, 442 });

	continueButton->SetActive(false);

	// 리스타트 버튼
	UIButton* RestartButton = (UIButton*)AddGo(new UIButton("Ui/RestartButton.png", "Volume Off Button"));
	RestartButton->SetOrigin(Origins::MC);
	RestartButton->sortLayer = 101;
	RestartButton->SetPosition({ 632, 442 });

	RestartButton->SetActive(false);

	// 홈 버튼
	UIButton* HomeButton = (UIButton*)AddGo(new UIButton("Ui/HomeButton.png", "Volume Off Button"));
	HomeButton->SetOrigin(Origins::MC);
	HomeButton->sortLayer = 101;
	HomeButton->SetPosition({ 795, 441 });

	HomeButton->SetActive(false);

	// 퍼즈 보드판
	pauseBoard = (SpriteGo*)AddGo(new SpriteGo("Ui/pauseBoard.png", "Back Ground"));
	pauseBoard->SetOrigin(Origins::MC);
	pauseBoard->sortLayer = 100;
	pauseBoard->SetPosition(size.x / 2, size.y / 2);

	pauseBoard->SetActive(false);

	{
		sf::Color gammaColor(100, 100, 100, 255);

		startButton->OnEnter = [startButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/startButton.png");
			startButton->sprite.setColor(gammaColor);
		};
		pauseButton->OnEnter = [pauseButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/pauseButton.png");
			pauseButton->sprite.setColor(gammaColor);
		};
		pauseButton->OnEnter = [pauseButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/pauseButton.png");
			pauseButton->sprite.setColor(gammaColor);
		};
		volumeOnButton->OnEnter = [volumeOnButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/volumeOnButton.png");
			volumeOnButton->sprite.setColor(gammaColor);
		};
		volumeOffButton->OnEnter = [volumeOffButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/volumeOffButton.png");
			volumeOffButton->sprite.setColor(gammaColor);
		};
		continueButton->OnEnter = [continueButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/continueButton.png");
			continueButton->sprite.setColor(gammaColor);
		};
		RestartButton->OnEnter = [RestartButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/RestartButton.png");
			RestartButton->sprite.setColor(gammaColor);
		};
		HomeButton->OnEnter = [HomeButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/HomeButton.png");
			HomeButton->sprite.setColor(gammaColor);
		};

		startButton->OnExit = [startButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/startButton.png");
			startButton->sprite.setColor(sf::Color::White);
		};
		pauseButton->OnExit = [pauseButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/pauseButton.png");
			pauseButton->sprite.setColor(sf::Color::White);
		};
		volumeOnButton->OnExit = [volumeOnButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/volumeOnButton.png");
			volumeOnButton->sprite.setColor(sf::Color::White);
		};
		volumeOffButton->OnExit = [volumeOffButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/volumeOffButton.png");
			volumeOffButton->sprite.setColor(sf::Color::White);
		};
		continueButton->OnExit = [continueButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/continueButton.png");
			continueButton->sprite.setColor(sf::Color::White);
		};
		RestartButton->OnExit = [RestartButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/RestartButton.png");
			RestartButton->sprite.setColor(sf::Color::White);
		};
		HomeButton->OnExit = [HomeButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/HomeButton.png");
			HomeButton->sprite.setColor(sf::Color::White);
		};

		startButton->OnClick = [this, startButton]()
		{
			raceMode = 0.0f;
			isRoundStart = !isRoundStart;
			//SpawnEnemys(1, Enemy::Types::Ufo1);
			std::cout << "몬스터 생성!" << std::endl;
		};
		pauseButton->OnClick = [this, pauseButton, continueButton, RestartButton, HomeButton]()
		{
			SCENE_MGR.SetdtSpeed(0);
			pauseBoard->SetActive(true);
			continueButton->SetActive(true);
			RestartButton->SetActive(true);
			HomeButton->SetActive(true);
			std::cout << "일시정지!" << std::endl;
		};
		volumeOnButton->OnClick = [this, volumeOnButton, volumeOffButton, volumeOnOff]()
		{
			
			volumeOnButton->SetActive(!volumeOnOff);
			volumeOffButton->SetActive(volumeOnOff);
			std::cout << "볼륨 on!" << std::endl;
		};
		volumeOffButton->OnClick = [this, volumeOnButton, volumeOffButton, volumeOnOff]()
		{
			volumeOffButton->SetActive(!volumeOnOff);
			volumeOnButton->SetActive(volumeOnOff);
			std::cout << "볼륨 off!" << std::endl;
		};
		continueButton->OnClick = [this, pauseButton, continueButton, RestartButton, HomeButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			continueButton->SetActive(false);
			pauseBoard->SetActive(false);
			RestartButton->SetActive(false);
			HomeButton->SetActive(false);
		};
		RestartButton->OnClick = [this, pauseButton, continueButton, RestartButton, HomeButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			RestartButton->SetActive(false);
			continueButton->SetActive(false);
			HomeButton->SetActive(false);
			
		};
		HomeButton->OnClick = [this, pauseButton, continueButton, RestartButton, HomeButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			continueButton->SetActive(false);
			RestartButton->SetActive(false);
			HomeButton->SetActive(false);
			SCENE_MGR.ChangeScene(SceneId::Title);
		};

	}

	// 텍스트

	goldText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Scene Name"));
	goldText->sortLayer = 100;
	goldText->text.setCharacterSize(23);
	goldText->text.setFillColor(sf::Color::Yellow);
	goldText->text.setString(L"Gold: 320"); // 임시값
	goldText->SetPosition(75, 15);

	waveText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Scene Name"));
	waveText->sortLayer = 100;
	waveText->text.setCharacterSize(23);
	waveText->text.setFillColor(sf::Color::White);
	waveText->text.setString(L"Wave 1/10"); // 임시값
	waveText->SetPosition(75, 65);

	lifeText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Scene Name"));
	lifeText->sortLayer = 100;
	lifeText->text.setCharacterSize(23);
	lifeText->text.setFillColor(sf::Color::Red);
	lifeText->text.setString(L"Life: 15"); // 임시값
	lifeText->SetPosition(75, 115);




	tileMap = (TileMap*)AddGo(new TileMap("graphics/grass.png", "Tile Map"));

	// 몬스터 오브젝트풀

	enemyPool.OnCreate = [this](Enemy* enemy)
	{
		/*Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 1);
		enemy->SetType(enemyType);*/
		enemy->SetType(Enemy::Types::Ufo1);
		enemy->SetTowerList(GetTowerList()); // 추가오류
		//enemy->SetEnemyList(GetEnemyList());
	};
	enemyPool.Init();

	// 애로우 오브젝트풀

	arrowPool.OnCreate = [this](Arrow* arrow)
	{
		Arrow::Types arrowType = (Arrow::Types)Utils::RandomRange(0, Arrow::TotalTypes - 1);
		arrow->SetType(arrowType);
		arrow->SetEnemyList(GetEnemyList());
		arrow->GetArrowPool(&arrowPool); // 추가
	};
	arrowPool.Init();

	// 타워 오브젝트풀
	// 참조해야하는 부분에 포인터로 참조해야하는 부분은 참조해라 // 널로 된게 많아서
	// 온 크리에이트 부분에서 초기화 초기화 신경쓰기

	towerPool.OnCreate = [this](Tower* tower) {
		tower->GetArrowPool(&arrowPool);
		tower->SetType(Tower::Types::ArcherTower1);
		tower->SetEnemyList(GetEnemyList());
		tower->SetArrowList(GetArrowList());
	};
	towerPool.Init();

	// 오브젝트 오브젝트풀

	objectPool.OnCreate = [this](Object* object)
	{
		Object::Types objectType = (Object::Types)Utils::RandomRange(0, Object::TotalTypes - 1);
		object->SetType(objectType);
	};
	objectPool.Init();

	// 몬스터 죽었을때 이펙트

	goldEffectPool.OnCreate = [this](SpriteEffect* effect)
	{
		effect->SetDuration(1.0f);
		effect->SetPool(&goldEffectPool);
	};
	goldEffectPool.Init();


	for (auto go : gameObjects)
	{
		go->Init();
	}

	tileMap->Load("map/map2.csv");
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetPosition(size * 0.5f);
	tileMap->sortOrder = -1;

	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);


	{

		diamond1.setPointCount(4);
		diamond1.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
		diamond1.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
		diamond1.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
		diamond1.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
		diamond1.setFillColor(sf::Color::Green);
		diamond1.setPosition(569, 160);

		diamond2.setPointCount(4);
		diamond2.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
		diamond2.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
		diamond2.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
		diamond2.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
		diamond2.setFillColor(sf::Color::Green);
		diamond2.setPosition(838, 211);

		diamond3.setPointCount(4);
		diamond3.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
		diamond3.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
		diamond3.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
		diamond3.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
		diamond3.setFillColor(sf::Color::Green);
		diamond3.setPosition(613, 340);

		diamond4.setPointCount(4);
		diamond4.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
		diamond4.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
		diamond4.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
		diamond4.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
		diamond4.setFillColor(sf::Color::Green);
		diamond4.setPosition(883, 392);

		diamond5.setPointCount(4);
		diamond5.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
		diamond5.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
		diamond5.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
		diamond5.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
		diamond5.setFillColor(sf::Color::Green);
		diamond5.setPosition(748, 469);

		diamond6.setPointCount(4);
		diamond6.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
		diamond6.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
		diamond6.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
		diamond6.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
		diamond6.setFillColor(sf::Color::Green);
		diamond6.setPosition(1063, 442);

	}


}

void SceneDev1::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneDev1::Enter()
{
	Scene::Enter();
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);
	{
		// 버튼 위치 업데이트
		trigger += dt / targetDuration;

		if (trigger > 1.0f)
			trigger = 1.0f;

		sf::Vector2f newPosition = currentPosition + (targetPosition - currentPosition) * trigger;
		roundStart->SetPosition(newPosition);
		//std::cout << "newPosition: " << newPosition.x << ", " << newPosition.y << std::endl;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Dev2);
	}

	raceMode += dt;
	//std::cout << "raceMode: " << raceMode << std::endl;
	if (raceMode >= reaceModeCount)
	{
		isRoundStart = !isRoundStart;
		raceMode = 0.f;
	}

	if (isRoundStart && roundCheck == 1)
		/*&& 이 부분에 몬스터가 맵에 없는경우 추가 )*/
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: "<< roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo1);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			//std::cout << "roundCheck: " << roundCheck << std::endl;
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /10";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));

			std::cout << "roundCheck: " << roundCheck << " - 5초후 다음 라운드 강제시작" << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}
	else if (isRoundStart && roundCheck == 2)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo2);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /10";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}
	else if (isRoundStart && roundCheck == 3)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo3);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /10";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}
	else if (isRoundStart && roundCheck == 4)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo4);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /10";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}
	else if (isRoundStart && roundCheck == 5)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo5);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /10";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}
	else if (isRoundStart && roundCheck == 6)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo6);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /10";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}
	else if (isRoundStart && roundCheck == 7)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo7);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /10";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}
	

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = ScreenToUiPos(mousePos);

	// 마우스 좌표 테스트
	// std::cout << "마우스x: " << uiMousePos.x << "마우스y: "<< uiMousePos.y << std::endl;
	// 마우스 좌표 테스트

	Test();


	bool isHover = false;
	bool prevHover = isHover;


	if (!prevHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f tileSize = { 90, 85 };

		TileMap tile;

		sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
		sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
		sf::Vector2f isoTileCoords = tile.screenToIsoTileCoords(uiMousePos, sf::Vector2f(tileSize.x, tileSize.y));

		std::cout << "Clicked Isometric Tile: (" << isoTileCoords.x << ", " << isoTileCoords.y << ")" << std::endl;
	}

	// 마름모 충돌체크

	bool isColliding = true;

	{
		diaBounds = diamond1.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "충돌체크1" << std::endl;
			towerBuildCheck1 = !towerBuildCheck1;
		}

		if (!towerBuildCheck1 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		{
			BuildTower(Tower::Types::ArcherTower1, { 586, 197 });
			towerBuildCheck1 = !towerBuildCheck1;
		}
		else if (!towerBuildCheck1 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		{
			BuildTower(Tower::Types::WizardTower1, { 586, 197 });
			towerBuildCheck1 = !towerBuildCheck1;
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::T))
		{
			testHide = !testHide;
		}
	}

	{
		diaBounds = diamond2.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "충돌체크2" << std::endl;
			towerBuildCheck2 = !towerBuildCheck2;
		}

		if (!towerBuildCheck2 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		{
			BuildTower(Tower::Types::ArcherTower1, { 857, 248 });
			towerBuildCheck2 = !towerBuildCheck2;
		}
		else if (!towerBuildCheck2 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		{
			BuildTower(Tower::Types::WizardTower1, { 857, 248 });
			towerBuildCheck2 = !towerBuildCheck2;
		}
	}

	{
		diaBounds = diamond3.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "충돌체크3" << std::endl;
			towerBuildCheck3 = !towerBuildCheck3;
		}

		if (!towerBuildCheck3 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		{
			BuildTower(Tower::Types::ArcherTower1, { 632, 376 });
			towerBuildCheck3 = !towerBuildCheck3;
		}
		else if (!towerBuildCheck3 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		{
			BuildTower(Tower::Types::WizardTower1, { 632, 376 });
			towerBuildCheck3 = !towerBuildCheck3;
		}
	}

	{
		diaBounds = diamond4.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "충돌체크4" << std::endl;
			towerBuildCheck4 = !towerBuildCheck4;
		}

		if (!towerBuildCheck4 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		{
			BuildTower(Tower::Types::ArcherTower1, { 902, 428 });
			towerBuildCheck4 = !towerBuildCheck4;
		}
		else if (!towerBuildCheck4 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		{
			BuildTower(Tower::Types::WizardTower1, { 902, 428 });
			towerBuildCheck4 = !towerBuildCheck4;
		}
	}

	{
		diaBounds = diamond5.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "충돌체크5" << std::endl;
			towerBuildCheck5 = !towerBuildCheck5;
		}

		if (!towerBuildCheck5 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		{
			BuildTower(Tower::Types::ArcherTower1, { 767, 505 });
			towerBuildCheck5 = !towerBuildCheck5;
		}
		else if (!towerBuildCheck5 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		{
			BuildTower(Tower::Types::WizardTower1, { 767, 505 });
			towerBuildCheck5 = !towerBuildCheck5;
		}
	}

	{
		diaBounds = diamond6.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "충돌체크6" << std::endl;
			towerBuildCheck6 = !towerBuildCheck6;
		}

		if (!towerBuildCheck6 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		{
			BuildTower(Tower::Types::ArcherTower1, { 1082, 479 });
			towerBuildCheck6 = !towerBuildCheck6;
		}
		else if (!towerBuildCheck6 && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		{
			BuildTower(Tower::Types::WizardTower1, { 1082, 479 });
			towerBuildCheck6 = !towerBuildCheck6;
		}
	}

}


void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	if (testHide)
	{
		window.draw(diamond1);
		window.draw(diamond2);
		window.draw(diamond3);
		window.draw(diamond4);
		window.draw(diamond5);
		window.draw(diamond6);
	}
}

void SceneDev1::BuildObject(int count, sf::Vector2f pos)
{
	// 45, 76
	// 91, 100 우 대각 // 46, 24 차이
	// 145, 76 오른쪽 // x값 90차이
	// 45, 127 바로아래 // y값 51차이

	sf::Vector2f objPos = { 45, 56 };

	sf::Vector2f tileSize = { 90.f, 85.f };
	
	sf::Vector2f currPos = objPos;

	float widthDifference = tileSize.x * 0.5f;
	float heightDifference = tileSize.y * 0.3025f;

	for (int i = 0; i < count; ++i)
	{
		Object* object = objectPool.Get();
		
		object->SetPosition(currPos.x, currPos.y);
		for (int j = 0; j < count; ++j)
		{
			currPos.x += tileSize.x;
			//object->SetPosition(currPos.x, objPos.y);
		}
		
		currPos.x = objPos.x; // 사실상 스타트 포즈

		if (i % 2 == 0)
		{
			currPos.x += widthDifference;
			//object->SetPosition(currPos.x, objPos.y);
		}
	
		currPos.y += heightDifference;
		//object->SetPosition(currPos.x, currPos.y);
		// 변경
		AddGo(object);
	}

}

void SceneDev1::SetEnemyList(const std::list<Enemy*>* list)
{
	enemys = list;
}

void SceneDev1::SpawnEnemys(int enemyCount, Enemy::Types type)// 레디우스
{
	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* enemy = enemyPool.Get();
		enemy->SetType(type);
		enemy->SetPosition(358, -17);
		AddGo(enemy);
		//std::this_thread::sleep_for(std::chrono::milliseconds(regentime));
	}
}

void SceneDev1::OnDieEnemy(Enemy* enemy)
{
	
	

	gold += 3; // 몬스터 타입따라서 골드추가

	std::string goldString = "Gold: " + std::to_string(gold);
	goldText->text.setString(sf::String::fromUtf8(goldString.begin(), goldString.end()));

	//SpriteEffect* goldE = 

	RemoveGo(enemy);
	enemyPool.Return(enemy);
}

void SceneDev1::EnemyEndPoint(Enemy* enemy)
{
	// 라이프 감소 1씩 적용
	if (enemy->HasrealEndPoint())
	{
		return;
	}
	enemy->SetrealEndPoint(true);

	RemoveGo(enemy);
	enemyPool.Return(enemy);

	sf::Vector2f endPoint = { 1270.f, 504.f };
	if ((Utils::Distance(enemy->GetPosition(), endPoint)))
	{
		life--;
	}
	

	if (life = 0)
	{
		// 게임오버 처리
		// life = 0;
	}

	std::string lifeString = "Life: " + std::to_string(life);
	lifeText->text.setString(sf::String::fromUtf8(lifeString.begin(), lifeString.end()));
}

const std::list<Enemy*>* SceneDev1::GetEnemyList() const
{
	return &enemyPool.GetUseList();
}

const std::list<Arrow*>* SceneDev1::GetArrowList() const
{
	return &arrowPool.GetUseList();
}

const std::list<Tower*>* SceneDev1::GetTowerList() const
{
	return &towerPool.GetUseList();
}

//void SceneDev1::TowerAttack()
//{
//
//
//}

void SceneDev1::BuildTower(Tower::Types towerType, sf::Vector2f pos)
{
	Tower* tower = towerPool.Get();
	tower->SetType(towerType);
	tower->SetPosition(pos);
	tower->Reset();
	UpdateGold(80);
	AddGo(tower);

	std::cout << tower->GetPosition().x << " , " << tower->GetPosition().y << std::endl;
}

void SceneDev1::UpdateGold(int amount)
{
	gold -= amount;
	std::string goldString = "Gold: " + std::to_string(gold);
	goldText->text.setString(sf::String::fromUtf8(goldString.begin(), goldString.end()));
}

void SceneDev1::Test()
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		raceMode = 0.0f;
		isRoundStart = !isRoundStart;
		//SpawnEnemys(3, 2000);
		std::cout << "몬스터 생성!" << std::endl;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::C))
	{
		ClearObjectPool(enemyPool);
		ClearObjectPool(towerPool);
		ClearObjectPool(arrowPool);
		ClearObjectPool(objectPool);

		std::cout << "삭제 완료!" << std::endl;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::O))
	{
		BuildObject(25, { 0,0 });
		std::cout << "오브젝트 생성!" << std::endl;
	}


}

void SceneDev1::StartGame()
{
}

void SceneDev1::StartRound()
{
}

void SceneDev1::EndRound()
{
}

void SceneDev1::StartStage()
{
}

void SceneDev1::EndStage()
{
}

void SceneDev1::SaveFile()
{
}
