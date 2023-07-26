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


SceneDev1::SceneDev1() : Scene(SceneId::Dev1), tower(nullptr), goldCoin("", "Gold Coin")
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

	basicArcher = (SpriteGo*)AddGo(new SpriteGo("Ui/basicArcher.png", "Basic Archer"));
	basicArcher->SetOrigin(Origins::MC);
	basicArcher->sortLayer = 300;
	basicArcher->SetPosition(size.x / 2, size.y / 2);
	basicArcher->SetActive(false);

	upgradeArcher2 = (SpriteGo*)AddGo(new SpriteGo("Ui/UpgradeArcher2.png", "Upgrade Archer2"));
	upgradeArcher2->SetOrigin(Origins::MC);
	upgradeArcher2->sortLayer = 300;
	upgradeArcher2->SetPosition(size.x / 2, size.y / 2);
	upgradeArcher2->SetActive(false);

	upgradeArcher3 = (SpriteGo*)AddGo(new SpriteGo("Ui/UpgradeArcher3.png", "Upgrade Archer3"));
	upgradeArcher3->SetOrigin(Origins::MC);
	upgradeArcher3->sortLayer = 300;
	upgradeArcher3->SetPosition(size.x / 2, size.y / 2);
	upgradeArcher3->SetActive(false);

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
	
	// 타워 설치 및 업그레이드 1
	UIButton* basicBuildButton = (UIButton*)AddGo(new UIButton("Ui/basicBuildButton.png", "Basic Build Button"));
	basicBuildButton->SetOrigin(Origins::MC);
	basicBuildButton->sortLayer = 301;
	basicBuildButton->SetPosition({ 770, 570 });
	basicBuildButton->SetActive(false);

	UIButton* upgradeButton = (UIButton*)AddGo(new UIButton("Ui/upgradeButton.png", "Upgrade Button"));
	upgradeButton->SetOrigin(Origins::MC);
	upgradeButton->sortLayer = 301;
	upgradeButton->SetPosition({ 770, 570 });
	upgradeButton->SetActive(false);

	UIButton* upgradeButton2 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton2.png", "Upgrade Button2"));
	upgradeButton2->SetOrigin(Origins::MC);
	upgradeButton2->sortLayer = 301;
	upgradeButton2->SetPosition({ 770, 570 });
	upgradeButton2->SetActive(false);

	// 타워 설치 및 업그레이드 2
	UIButton* basicBuildButton2 = (UIButton*)AddGo(new UIButton("Ui/basicBuildButton2.png", "Basic Build Button2"));
	basicBuildButton2->SetOrigin(Origins::MC);
	basicBuildButton2->sortLayer = 301;
	basicBuildButton2->SetPosition({ 770, 570 });
	basicBuildButton2->SetActive(false);

	UIButton* upgradeButton2e = (UIButton*)AddGo(new UIButton("Ui/upgradeButton2e.png", "Upgrade Button2e"));
	upgradeButton2e->SetOrigin(Origins::MC);
	upgradeButton2e->sortLayer = 301;
	upgradeButton2e->SetPosition({ 770, 570 });
	upgradeButton2e->SetActive(false);

	UIButton* upgradeButton22 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton22.png", "Upgrade Button22"));
	upgradeButton22->SetOrigin(Origins::MC);
	upgradeButton22->sortLayer = 301;
	upgradeButton22->SetPosition({ 770, 570 });
	upgradeButton22->SetActive(false);

	// 타워 설치 및 업그레이드 3
	UIButton* basicBuildButton3 = (UIButton*)AddGo(new UIButton("Ui/basicBuildButton3.png", "Basic Build Button3"));
	basicBuildButton3->SetOrigin(Origins::MC);
	basicBuildButton3->sortLayer = 301;
	basicBuildButton3->SetPosition({ 770, 570 });
	basicBuildButton3->SetActive(false);

	UIButton* upgradeButton3 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton3.png", "Upgrade Button3"));
	upgradeButton3->SetOrigin(Origins::MC);
	upgradeButton3->sortLayer = 301;
	upgradeButton3->SetPosition({ 770, 570 });
	upgradeButton3->SetActive(false);

	UIButton* upgradeButton33 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton33.png", "Upgrade Button33"));
	upgradeButton33->SetOrigin(Origins::MC);
	upgradeButton33->sortLayer = 301;
	upgradeButton33->SetPosition({ 770, 570 });
	upgradeButton33->SetActive(false);

	// 타워 설치 및 업그레이드 4
	UIButton* basicBuildButton4 = (UIButton*)AddGo(new UIButton("Ui/basicBuildButton4.png", "Basic Build Button4"));
	basicBuildButton4->SetOrigin(Origins::MC);
	basicBuildButton4->sortLayer = 301;
	basicBuildButton4->SetPosition({ 770, 570 });
	basicBuildButton4->SetActive(false);

	UIButton* upgradeButton4 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton4.png", "Upgrade Button4"));
	upgradeButton4->SetOrigin(Origins::MC);
	upgradeButton4->sortLayer = 301;
	upgradeButton4->SetPosition({ 770, 570 });
	upgradeButton4->SetActive(false);

	UIButton* upgradeButton44 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton44.png", "Upgrade Button44"));
	upgradeButton44->SetOrigin(Origins::MC);
	upgradeButton44->sortLayer = 301;
	upgradeButton44->SetPosition({ 770, 570 });
	upgradeButton44->SetActive(false);

	// 타워 설치 및 업그레이드 5
	UIButton* basicBuildButton5 = (UIButton*)AddGo(new UIButton("Ui/basicBuildButton5.png", "Basic Build Button5"));
	basicBuildButton5->SetOrigin(Origins::MC);
	basicBuildButton5->sortLayer = 301;
	basicBuildButton5->SetPosition({ 770, 570 });
	basicBuildButton5->SetActive(false);

	UIButton* upgradeButton5 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton5.png", "Upgrade Button5"));
	upgradeButton5->SetOrigin(Origins::MC);
	upgradeButton5->sortLayer = 301;
	upgradeButton5->SetPosition({ 770, 570 });
	upgradeButton5->SetActive(false);

	UIButton* upgradeButton55 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton55.png", "Upgrade Button55"));
	upgradeButton55->SetOrigin(Origins::MC);
	upgradeButton55->sortLayer = 301;
	upgradeButton55->SetPosition({ 770, 570 });
	upgradeButton55->SetActive(false);

	// 타워 설치 및 업그레이드 6
	UIButton* basicBuildButton6 = (UIButton*)AddGo(new UIButton("Ui/basicBuildButton6.png", "Basic Build Button6"));
	basicBuildButton6->SetOrigin(Origins::MC);
	basicBuildButton6->sortLayer = 301;
	basicBuildButton6->SetPosition({ 770, 570 });
	basicBuildButton6->SetActive(false);

	UIButton* upgradeButton6 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton6.png", "Upgrade Button6"));
	upgradeButton6->SetOrigin(Origins::MC);
	upgradeButton6->sortLayer = 301;
	upgradeButton6->SetPosition({ 770, 570 });
	upgradeButton6->SetActive(false);

	UIButton* upgradeButton66 = (UIButton*)AddGo(new UIButton("Ui/upgradeButton66.png", "Upgrade Button66"));
	upgradeButton66->SetOrigin(Origins::MC);
	upgradeButton66->sortLayer = 301;
	upgradeButton66->SetPosition({ 770, 570 });
	upgradeButton66->SetActive(false);



	UIButton* giveupButton = (UIButton*)AddGo(new UIButton("Ui/giveupButton.png", "Giveup Button"));
	giveupButton->SetOrigin(Origins::MC);
	giveupButton->sortLayer = 301;
	giveupButton->SetPosition({ 1025, 619 });
	giveupButton->SetActive(false);

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
		giveupButton->OnEnter = [giveupButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/giveupButton.png");
			giveupButton->sprite.setColor(gammaColor);
		};
		basicBuildButton->OnEnter = [basicBuildButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton.png");
			basicBuildButton->sprite.setColor(gammaColor);
		};
		upgradeButton->OnEnter = [upgradeButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton.png");
			upgradeButton->sprite.setColor(gammaColor);
		};
		upgradeButton2->OnEnter = [upgradeButton2, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton2.png");
			upgradeButton2->sprite.setColor(gammaColor);
		};
		basicBuildButton2->OnEnter = [basicBuildButton2, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton2.png");
			basicBuildButton2->sprite.setColor(gammaColor);
		};
		upgradeButton2e->OnEnter = [upgradeButton2e, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton2e.png");
			upgradeButton2e->sprite.setColor(gammaColor);
		};
		upgradeButton22->OnEnter = [upgradeButton22, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton22.png");
			upgradeButton22->sprite.setColor(gammaColor);
		};
		basicBuildButton3->OnEnter = [basicBuildButton3, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton3.png");
			basicBuildButton3->sprite.setColor(gammaColor);
		};
		upgradeButton3->OnEnter = [upgradeButton3, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton3.png");
			upgradeButton3->sprite.setColor(gammaColor);
		};
		upgradeButton33->OnEnter = [upgradeButton33, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton33.png");
			upgradeButton33->sprite.setColor(gammaColor);
		};
		basicBuildButton4->OnEnter = [basicBuildButton4, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton4.png");
			basicBuildButton4->sprite.setColor(gammaColor);
		};
		upgradeButton4->OnEnter = [upgradeButton4, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton4.png");
			upgradeButton4->sprite.setColor(gammaColor);
		};
		upgradeButton44->OnEnter = [upgradeButton44, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton44.png");
			upgradeButton44->sprite.setColor(gammaColor);
		};
		basicBuildButton5->OnEnter = [basicBuildButton5, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton5.png");
			basicBuildButton5->sprite.setColor(gammaColor);
		};
		upgradeButton5->OnEnter = [upgradeButton5, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton5.png");
			upgradeButton5->sprite.setColor(gammaColor);
		};
		upgradeButton55->OnEnter = [upgradeButton55, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton55.png");
			upgradeButton55->sprite.setColor(gammaColor);
		};
		basicBuildButton6->OnEnter = [basicBuildButton6, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton6.png");
			basicBuildButton6->sprite.setColor(gammaColor);
		};
		upgradeButton6->OnEnter = [upgradeButton6, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton6.png");
			upgradeButton6->sprite.setColor(gammaColor);
		};
		upgradeButton66->OnEnter = [upgradeButton66, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton66.png");
			upgradeButton66->sprite.setColor(gammaColor);
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
		giveupButton->OnExit = [giveupButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/giveupButton.png");
			giveupButton->sprite.setColor(sf::Color::White);
		};
		basicBuildButton->OnExit = [basicBuildButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton.png");
			basicBuildButton->sprite.setColor(sf::Color::White);
		};
		upgradeButton->OnExit = [upgradeButton, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton.png");
			upgradeButton->sprite.setColor(sf::Color::White);
		};
		upgradeButton2->OnExit = [upgradeButton2, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton2.png");
			upgradeButton2->sprite.setColor(sf::Color::White);
		};
		basicBuildButton2->OnExit = [basicBuildButton2, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton2.png");
			basicBuildButton2->sprite.setColor(sf::Color::White);
		};
		upgradeButton2e->OnExit = [upgradeButton2e, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton2e.png");
			upgradeButton2e->sprite.setColor(sf::Color::White);
		};
		upgradeButton22->OnExit = [upgradeButton22, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton22.png");
			upgradeButton22->sprite.setColor(sf::Color::White);
		};
		basicBuildButton3->OnExit = [basicBuildButton3, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton3.png");
			basicBuildButton3->sprite.setColor(sf::Color::White);
		};
		upgradeButton3->OnExit = [upgradeButton3, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton3.png");
			upgradeButton3->sprite.setColor(sf::Color::White);
		};
		upgradeButton33->OnExit = [upgradeButton33, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton33.png");
			upgradeButton33->sprite.setColor(sf::Color::White);
		};
		basicBuildButton4->OnExit = [basicBuildButton4, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton4.png");
			basicBuildButton4->sprite.setColor(sf::Color::White);
		};
		upgradeButton4->OnExit = [upgradeButton4, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton4.png");
			upgradeButton4->sprite.setColor(sf::Color::White);
		};
		upgradeButton44->OnExit = [upgradeButton44, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton44.png");
			upgradeButton44->sprite.setColor(sf::Color::White);
		};
		basicBuildButton5->OnExit = [basicBuildButton5, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton5.png");
			basicBuildButton5->sprite.setColor(sf::Color::White);
		};
		upgradeButton5->OnExit = [upgradeButton5, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton5.png");
			upgradeButton5->sprite.setColor(sf::Color::White);
		};
		upgradeButton55->OnExit = [upgradeButton55, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton55.png");
			upgradeButton55->sprite.setColor(sf::Color::White);
		};
		basicBuildButton6->OnExit = [basicBuildButton6, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/basicBuildButton6.png");
			basicBuildButton6->sprite.setColor(sf::Color::White);
		};
		upgradeButton6->OnExit = [upgradeButton6, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton6.png");
			upgradeButton6->sprite.setColor(sf::Color::White);
		};
		upgradeButton66->OnExit = [upgradeButton66, gammaColor]()
		{
			sf::Texture* tex = RESOURCE_MGR.GetTexture("Ui/upgradeButton66.png");
			upgradeButton66->sprite.setColor(sf::Color::White);
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
		HomeButton->OnClick = [this, pauseButton, continueButton, RestartButton, HomeButton, background, startButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			continueButton->SetActive(false);
			RestartButton->SetActive(false);
			HomeButton->SetActive(false);
			//background->SetActive(false);
			startButton->SetActive(true);
			ResetGame();
			Scene::Exit();
			gold = 320;
			wave = 1;   //작동안됨
			
			SCENE_MGR.ChangeScene(SceneId::Title);
		};
		giveupButton->OnClick = [this, giveupButton, basicBuildButton, basicBuildButton2, basicBuildButton3, basicBuildButton4, basicBuildButton5, basicBuildButton6, upgradeButton, upgradeButton2e, upgradeButton3, upgradeButton4, upgradeButton5, upgradeButton6, upgradeButton2, upgradeButton22, upgradeButton33, upgradeButton44, upgradeButton55, upgradeButton66]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);

			basicArcher->SetActive(false);
			upgradeArcher3->SetActive(false);
			upgradeArcher2->SetActive(false);
			basicText->SetActive(false);
			buyText->SetActive(false);
			upgradeText2->SetActive(false);
			upgradeText3->SetActive(false);

			basicBuildButton->SetActive(false);
			basicBuildButton2->SetActive(false);
			basicBuildButton3->SetActive(false);
			basicBuildButton4->SetActive(false);
			basicBuildButton5->SetActive(false);
			basicBuildButton6->SetActive(false);

			upgradeButton->SetActive(false);
			upgradeButton2e->SetActive(false);
			upgradeButton3->SetActive(false);
			upgradeButton4->SetActive(false);
			upgradeButton5->SetActive(false);
			upgradeButton6->SetActive(false);

			upgradeButton2->SetActive(false);
			upgradeButton22->SetActive(false);
			upgradeButton33->SetActive(false);
			upgradeButton44->SetActive(false);
			upgradeButton55->SetActive(false);
			upgradeButton66->SetActive(false);

		};
		basicBuildButton->OnClick = [this, basicBuildButton, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			basicBuildButton->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			basicArcher->SetActive(false);
			basicText->SetActive(false);
			if (gold > 80)
			{
				BuildTower(Tower::Types::ArcherTower1, { 586, 197 });
				towerbuildComplete1 = !towerbuildComplete1;
			}
			else
				return;
		};
		upgradeButton->OnClick = [this, upgradeButton, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			if (gold > 120)
			{
				BuildUpgradeTower(Tower::Types::ArcherTower2, { 586, 197 });
				towerUpgradeCheck1 = !towerUpgradeCheck1;
			}
			else
				return;
		};
		upgradeButton2->OnClick = [this, upgradeButton2, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton2->SetActive(false);
			upgradeArcher3->SetActive(false);
			upgradeText3->SetActive(false);
			buyText->SetActive(false);
			if (gold > 240)
			{
				BuildUpgradeTower2(Tower::Types::ArcherTower3, { 586, 197 });
			}
			else
				return;
		};
		
		basicBuildButton2->OnClick = [this, basicBuildButton2, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			basicBuildButton2->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			basicArcher->SetActive(false);
			basicText->SetActive(false);
			if (gold > 80)
			{
				BuildTower(Tower::Types::ArcherTower1, { 855, 248 });
				towerbuildComplete2 = !towerbuildComplete2;
			}
			else
				return;
		};
		upgradeButton2e->OnClick = [this, upgradeButton2e, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton2e->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			if (gold > 120)
			{
				BuildUpgradeTower(Tower::Types::ArcherTower2, { 855, 248 });
				towerUpgradeCheck2 = !towerUpgradeCheck2;
			}
			else
				return;
		};
		upgradeButton22->OnClick = [this, upgradeButton22, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton22->SetActive(false);
			upgradeArcher3->SetActive(false);
			upgradeText3->SetActive(false);
			buyText->SetActive(false);
			if (gold > 240)
			{
				BuildUpgradeTower2(Tower::Types::ArcherTower3, { 855, 248 });
			}
			else
				return;
		};

		basicBuildButton3->OnClick = [this, basicBuildButton3, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			basicBuildButton3->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			basicArcher->SetActive(false);
			basicText->SetActive(false);
			if (gold > 80)
			{
				BuildTower(Tower::Types::ArcherTower1, { 630, 377 });
				towerbuildComplete3 = !towerbuildComplete3;
			}
			else
				return;
		};
		upgradeButton3->OnClick = [this, upgradeButton3, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton3->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			if (gold > 120)
			{
				BuildUpgradeTower(Tower::Types::ArcherTower2, { 630, 377 });
				towerUpgradeCheck3 = !towerUpgradeCheck3;
			}
			else
				return;
		};
		upgradeButton33->OnClick = [this, upgradeButton33, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton33->SetActive(false);
			upgradeArcher3->SetActive(false);
			upgradeText3->SetActive(false);
			buyText->SetActive(false);
			if (gold > 240)
			{
				BuildUpgradeTower2(Tower::Types::ArcherTower3, { 630, 377 });
			}
			else
				return;
		};

		basicBuildButton4->OnClick = [this, basicBuildButton4, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			basicBuildButton4->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			basicArcher->SetActive(false);
			basicText->SetActive(false);
			if (gold > 80)
			{
				BuildTower(Tower::Types::ArcherTower1, { 900, 429 });
				towerbuildComplete4 = !towerbuildComplete4;
			}
			else
				return;
		};
		upgradeButton4->OnClick = [this, upgradeButton4, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton4->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			if (gold > 120)
			{
				BuildUpgradeTower(Tower::Types::ArcherTower2, { 900, 429 });
				towerUpgradeCheck4 = !towerUpgradeCheck4;
			}
			else
				return;
		};
		upgradeButton44->OnClick = [this, upgradeButton44, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton44->SetActive(false);
			upgradeArcher3->SetActive(false);
			upgradeText3->SetActive(false);
			buyText->SetActive(false);
			if (gold > 240)
			{
				BuildUpgradeTower2(Tower::Types::ArcherTower3, { 900, 429 });
			}
			else
				return;
		};

		basicBuildButton5->OnClick = [this, basicBuildButton5, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			basicBuildButton5->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			basicArcher->SetActive(false);
			basicText->SetActive(false);
			if (gold > 80)
			{
				BuildTower(Tower::Types::ArcherTower1, { 765, 506 });
				towerbuildComplete5 = !towerbuildComplete5;
			}
			else
				return;
		};
		upgradeButton5->OnClick = [this, upgradeButton5, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton5->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			if (gold > 120)
			{
				BuildUpgradeTower(Tower::Types::ArcherTower2, { 765, 506 });
				towerUpgradeCheck5 = !towerUpgradeCheck5;
			}
			else
				return;
		};
		upgradeButton55->OnClick = [this, upgradeButton55, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton55->SetActive(false);
			upgradeArcher3->SetActive(false);
			upgradeText3->SetActive(false);
			buyText->SetActive(false);
			if (gold > 240)
			{
				BuildUpgradeTower2(Tower::Types::ArcherTower3, { 765, 506 });
			}
			else
				return;
		};

		basicBuildButton6->OnClick = [this, basicBuildButton6, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			basicBuildButton6->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			basicArcher->SetActive(false);
			basicText->SetActive(false);
			if (gold > 80)
			{
				BuildTower(Tower::Types::ArcherTower1, { 1080, 479 });
				towerbuildComplete6 = !towerbuildComplete6;
			}
			else
				return;
		};
		upgradeButton6->OnClick = [this, upgradeButton6, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton6->SetActive(false);
			upgradeArcher2->SetActive(false);
			upgradeText2->SetActive(false);
			buyText->SetActive(false);
			if (gold > 120)
			{
				BuildUpgradeTower(Tower::Types::ArcherTower2, { 1080, 479 });
				towerUpgradeCheck6 = !towerUpgradeCheck6;
			}
			else
				return;
		};
		upgradeButton66->OnClick = [this, upgradeButton66, giveupButton]()
		{
			SCENE_MGR.SetdtSpeed(1);
			pauseBoard->SetActive(false);
			giveupButton->SetActive(false);
			upgradeButton66->SetActive(false);
			upgradeArcher3->SetActive(false);
			upgradeText3->SetActive(false);
			buyText->SetActive(false);
			if (gold > 240)
			{
				BuildUpgradeTower2(Tower::Types::ArcherTower3, { 1080, 479 });
			}
			else
				return;
		};

	}

	// 텍스트

	goldText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Gold Text"));
	goldText->sortLayer = 100;
	goldText->text.setCharacterSize(23);
	goldText->text.setFillColor(sf::Color::Yellow);
	goldText->text.setString(L"Gold: 320");
	goldText->SetPosition(75, 15);

	waveText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Wave Text"));
	waveText->sortLayer = 100;
	waveText->text.setCharacterSize(23);
	waveText->text.setFillColor(sf::Color::White);
	waveText->text.setString(L"Wave 1/21");
	waveText->SetPosition(75, 65);

	lifeText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Life Text"));
	lifeText->sortLayer = 100;
	lifeText->text.setCharacterSize(23);
	lifeText->text.setFillColor(sf::Color::Red);
	lifeText->text.setString(L"Life: 15");
	lifeText->SetPosition(75, 115);

	basicText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Basic Text"));
	basicText->sortLayer = 301;
	basicText->text.setCharacterSize(35);
	basicText->text.setFillColor(sf::Color::White);
	basicText->text.setString(L"Basic Archer\n\nFast Attack Speed↑\n\nDamage Up↑\n\nPrice: 80G"); // 임시값
	basicText->SetPosition(650, 150);
	basicText->SetActive(false);

	upgradeText2 = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Upgrade Text"));
	upgradeText2->sortLayer = 301;
	upgradeText2->text.setCharacterSize(35);
	upgradeText2->text.setFillColor(sf::Color::White);
	upgradeText2->text.setString(L"ArcherTower2\n\nFast Attack Speed↑\n\nDamage Up↑\n\nPrice: 120G"); // 임시값
	upgradeText2->SetPosition(650, 150);
	upgradeText2->SetActive(false);

	upgradeText3 = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Upgrade Text"));
	upgradeText3->sortLayer = 301;
	upgradeText3->text.setCharacterSize(35);
	upgradeText3->text.setFillColor(sf::Color::White);
	upgradeText3->text.setString(L"ArcherTower3\n\nSuper Fast Attack↑\n\nDamage Up↑\n\nPrice: 240G"); // 임시값
	upgradeText3->SetPosition(650, 150);
	upgradeText3->SetActive(false);

	buyText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Buy Text"));
	buyText->sortLayer = 301;
	buyText->text.setCharacterSize(35);
	buyText->text.setFillColor(sf::Color::White);
	buyText->text.setString(L"BUY"); // 임시값
	buyText->SetPosition(735, 545);
	buyText->SetActive(false);


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
	// 안씀

	/*goldEffectPool.OnCreate = [this](SpriteEffect* effect)
	{
		effect->textureId = "Ui/GoldCoinSheet.png";
		effect->SetDuration(1.0f);
		effect->SetPool(&goldEffectPool);
		effect->sortLayer = 200;
	};
	goldEffectPool.Init();*/


	// 골드 코인 애니메이션
	goldCoin.sortLayer = 200;
	goldCoin.SetOrigin(Origins::MC);
	goldCoin.textureId = "Ui/GoldCoinSheet.png";
	//goldCoin.SetPosition(500, 500); // 온 다이 몬스터에서
	AddGo(&goldCoin);
	goldAnimation.SetTarget(&goldCoin.sprite);
	goldAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/goldCoin.csv"));
	// 외워두기

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
	goldEffectPool.Release();
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneDev1::Enter()
{
	Scene::Enter();

	goldAnimation.Play("GoldAngle");
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	goldAnimation.Update(dt);
	animation.Update(dt);
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
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
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
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
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
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
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
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
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
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
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
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
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
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 8)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo8);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 9)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo9);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 10)
	{
		enemytrigger += dt;
		if (enemytrigger >= 3.f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo10);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 11)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo11);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 12)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo12);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 13)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo13);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 14)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo14);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 15)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo15);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 16)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo16);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 17)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo17);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 18)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo18);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 19)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo19);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 20)
	{
		enemytrigger += dt;
		if (enemytrigger >= 1.5f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo20);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
			waveText->text.setString(sf::String::fromUtf8(waveString.begin(), waveString.end()));
			std::cout << "roundCheck: " << roundCheck << std::endl;
			isRoundStart = !isRoundStart;
			roundTotalEnemy = 0;
		}
	}

	else if (isRoundStart && roundCheck == 21)
	{
		enemytrigger += dt;
		if (enemytrigger >= 5.f)
		{
			roundTotalEnemy++;
			std::cout << "enemytrigger: " << enemytrigger << std::endl;
			std::cout << "roundTotalEnemy: " << roundTotalEnemy << "/" << roundCountEnemy << std::endl;
			SpawnEnemys(1, Enemy::Types::Ufo21);
			enemytrigger = 0.f;
			raceMode = 0.f;
		}
		else if (roundTotalEnemy >= roundCountEnemy)
		{
			roundCheck++;
			wave++;
			std::string waveString = "Wave " + std::to_string(wave) + " /21";
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


	/*if (!prevHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f tileSize = { 90, 85 };

		TileMap tile;

		sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
		sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);
		sf::Vector2f isoTileCoords = tile.screenToIsoTileCoords(uiMousePos, sf::Vector2f(tileSize.x, tileSize.y));

		std::cout << "Clicked Isometric Tile: (" << isoTileCoords.x << ", " << isoTileCoords.y << ")" << std::endl;
	}*/

	// 마름모 충돌체크

	bool isColliding = true;

	{
		diaBounds = diamond1.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck1 && towerbuildComplete1 && !towerUpgradeComplete1)
		{
			SCENE_MGR.SetdtSpeed(0);
			basicText->SetActive(true);
			buyText->SetActive(true);
			FindGo("Basic Build Button")->SetActive(true);
			FindGo("Basic Archer")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}

		// 버튼쪽에서 타워 설치된순간 towerbuildComplete1펄스로 바뀜
		// 이제 위에꺼는 실행안됨

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck1 && !towerbuildComplete1 && !towerUpgradeComplete1)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText2->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button")->SetActive(true);
			FindGo("Upgrade Archer2")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}

		// 업그레이드 완료이후 towerUpgradeCheck1는 펄스로 바뀜
		// 이제 위에꺼는 실행안됨

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && !towerUpgradeCheck1 && !towerbuildComplete1)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText3->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button2")->SetActive(true);
			FindGo("Upgrade Archer3")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::T))
		{
			testHide = !testHide;
		}
	}

	// 타일 2 // 타일 2 // 타일 2 // 타일 2 // 타일 2 // 타일 2
	{
		diaBounds = diamond2.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck2 && towerbuildComplete2 && !towerUpgradeComplete2)
		{
			SCENE_MGR.SetdtSpeed(0);
			basicText->SetActive(true);
			buyText->SetActive(true);
			FindGo("Basic Build Button2")->SetActive(true);
			FindGo("Basic Archer")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck2 && !towerbuildComplete2 && !towerUpgradeComplete2)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText2->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button2e")->SetActive(true);
			FindGo("Upgrade Archer2")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && !towerUpgradeCheck2&& !towerbuildComplete2)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText3->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button22")->SetActive(true);
			FindGo("Upgrade Archer3")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
	}

	// 타일 3 // 타일 3 // 타일 3 // 타일 3 // 타일 3 // 타일 3 // 타일 3 
	{
		diaBounds = diamond3.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck3 && towerbuildComplete3 && !towerUpgradeComplete3)
		{
			SCENE_MGR.SetdtSpeed(0);
			basicText->SetActive(true);
			buyText->SetActive(true);
			FindGo("Basic Build Button3")->SetActive(true);
			FindGo("Basic Archer")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck3 && !towerbuildComplete3 && !towerUpgradeComplete3)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText2->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button3")->SetActive(true);
			FindGo("Upgrade Archer2")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && !towerUpgradeCheck3 && !towerbuildComplete3)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText3->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button33")->SetActive(true);
			FindGo("Upgrade Archer3")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
	}

	// 타일 4 // 타일 4 // 타일 4 // 타일 4 // 타일 4 // 타일 4 // 타일 4 
	{
		diaBounds = diamond4.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck4 && towerbuildComplete4 && !towerUpgradeComplete4)
		{
			SCENE_MGR.SetdtSpeed(0);
			basicText->SetActive(true);
			buyText->SetActive(true);
			FindGo("Basic Build Button4")->SetActive(true);
			FindGo("Basic Archer")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck4 && !towerbuildComplete4 && !towerUpgradeComplete4)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText2->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button4")->SetActive(true);
			FindGo("Upgrade Archer2")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && !towerUpgradeCheck4 && !towerbuildComplete4)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText3->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button44")->SetActive(true);
			FindGo("Upgrade Archer3")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
	}

	// 타일 5 // 타일 5 // 타일 5 // 타일 5 // 타일 5 // 타일 5 // 타일 5 
	{
		diaBounds = diamond5.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck5 && towerbuildComplete5 && !towerUpgradeComplete5)
		{
			SCENE_MGR.SetdtSpeed(0);
			basicText->SetActive(true);
			buyText->SetActive(true);
			FindGo("Basic Build Button5")->SetActive(true);
			FindGo("Basic Archer")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck5 && !towerbuildComplete5 && !towerUpgradeComplete5)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText2->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button5")->SetActive(true);
			FindGo("Upgrade Archer2")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && !towerUpgradeCheck5 && !towerbuildComplete5)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText3->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button55")->SetActive(true);
			FindGo("Upgrade Archer3")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
	}

	// 타일 6 // 타일 6 // 타일 6 // 타일 6 // 타일 6 // 타일 6 // 타일 6 
	{
		diaBounds = diamond6.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck6 && towerbuildComplete6 && !towerUpgradeComplete6)
		{
			SCENE_MGR.SetdtSpeed(0);
			basicText->SetActive(true);
			buyText->SetActive(true);
			FindGo("Basic Build Button6")->SetActive(true);
			FindGo("Basic Archer")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && towerUpgradeCheck6 && !towerbuildComplete6 && !towerUpgradeComplete6)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText2->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button6")->SetActive(true);
			FindGo("Upgrade Archer2")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
		}
		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left) && !towerUpgradeCheck6 && !towerbuildComplete6)
		{
			SCENE_MGR.SetdtSpeed(0);
			upgradeText3->SetActive(true);
			buyText->SetActive(true);
			FindGo("Upgrade Button66")->SetActive(true);
			FindGo("Upgrade Archer3")->SetActive(true);
			FindGo("Giveup Button")->SetActive(true);
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

	gold += 6; // 몬스터 타입따라서 골드추가 하고싶지만

	std::string goldString = "Gold: " + std::to_string(gold);
	goldText->text.setString(sf::String::fromUtf8(goldString.begin(), goldString.end()));

	

	goldCoin.SetPosition(enemy->GetPosition().x + 190, enemy->GetPosition().y);
	goldAnimation.Play("GoldAngle");


	//goldCoin.SetSize()




	//goldEffect->Anima




	//SpriteEffect* goldEffect = goldEffectPool.Get();
	//goldEffect->SetPosition(enemy->GetPosition());
	//AddGo(goldEffect);

	//float goldEffectSize = 0.5 + (1.0 - ((int)enemy->GetType() * 0.5));
	//float rot = Utils::RandomRange(0, 270);

	//goldEffect->SetSize(goldEffectSize, goldEffectSize);
	//goldEffect->sprite.setRotation(rot);
	////animation.Play("Idle");
	
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
		SCENE_MGR.SetdtSpeed(0);
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


void SceneDev1::BuildTower(Tower::Types towerType, sf::Vector2f pos)
{
	Tower* tower = towerPool.Get();
	tower->SetType(towerType);
	tower->SetPosition(pos);
	tower->Reset();
	UpdateGold(80);
	AddGo(tower);
}

void SceneDev1::BuildUpgradeTower(Tower::Types towerType, sf::Vector2f pos)
{
	// tower->SetActive(false);
	// towerPool.Return(tower); // 작동안됨

	Tower* tower = towerPool.Get();
	tower->SetType(towerType);
	tower->SetPosition(pos);
	tower->Reset();
	UpdateGold(120);
	AddGo(tower);
}

void SceneDev1::BuildUpgradeTower2(Tower::Types towerType, sf::Vector2f pos)
{
	Tower* tower = towerPool.Get();
	tower->SetType(towerType);
	tower->SetPosition(pos);
	tower->Reset();
	UpdateGold(240);
	AddGo(tower);
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

void SceneDev1::ResetGame()
{
	ClearObjectPool(enemyPool);
	ClearObjectPool(towerPool);
	ClearObjectPool(arrowPool);
	ClearObjectPool(objectPool);
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
