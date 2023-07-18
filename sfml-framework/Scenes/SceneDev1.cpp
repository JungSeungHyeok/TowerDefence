#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "TileMap.h"

#include "InputMgr.h"

#include "SoundGo.h"
#include "SpriteEffect.h"

#include "Enemy.h"
#include "Tower.h"

SceneDev1::SceneDev1() : Scene(SceneId::Dev1), tower(nullptr)
{
	/*resources.push_back(std::make_tuple(ResourceTypes::Texture, "Towers/Archer/archer_level_1.png"));*/

	resourceListPath = "scripts/SceneDev1ResourceList.csv";

	// csv로 보우 애니메이션만 추가하고
	// 타워 기본 이미지는 스프라이트 png 그냥 때려박고
	// csv로 보우 애니메이션만 추가하고
	// 타워 기본 이미지는 스프라이트 png 그냥 때려박고
}

void SceneDev1::Init()
{
	Release();

	sf::Vector2f size = FRAMEWORK.GetWindowSize();

	TextGo* sceneName = (TextGo*)AddGo(new TextGo("", "Scene Name"));
	sceneName->sortLayer = 100;
	sceneName->text.setCharacterSize(25);
	sceneName->text.setFillColor(sf::Color::White);
	sceneName->text.setString(L"타워디펜스");

	tileMap = (TileMap*)AddGo(new TileMap("graphics/grass.png", "Tile Map"));

	
	// tower addGo 제외


	// 몬스터 오브젝트풀

	enemyPool.OnCreate = [this](Enemy* enemy)
	{
		Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 1);
		enemy->SetType(enemyType);
	};
	enemyPool.Init();


	// 타워 오브젝트풀

	towerPool.OnCreate = [this](Tower* tower) {};
	towerPool.Init();



	for (auto go : gameObjects)
	{
		go->Init();
	}

	/*tower->SetOrigin(Origins::MC);
	tower->SetPosition(-500, 200);
	tower->sortLayer = 5;*/

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

	//enemy->SetPosition(uiMousePos);
}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{

	Scene::Update(dt);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Dev2);
	}

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = ScreenToUiPos(mousePos);

	// 마우스 좌표 테스트
	std::cout << "마우스x: " << uiMousePos.x << "마우스y: "<< uiMousePos.y << std::endl;
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





	TileMap tile;

	//sf::Vector2f tileSize = { 90, 85 };
	//sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	//sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
	//sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	/*sf::Vector2f isoTileCoords = tile.screenToIsoTileCoords(uiMousePos, sf::Vector2f(tileSize.x, tileSize.y));*/



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





		//if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		//{
		//	BuildTower(Tower::Types::ArcherTower1, { 586, 197 });
		//	towerBuildCheck = !towerBuildCheck;
		//}
		//else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		//{
		//	BuildTower(Tower::Types::ArcherTower2, { 586, 197 });
		//	towerBuildCheck = !towerBuildCheck;
		//}
		//else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
		//{
		//	BuildTower(Tower::Types::ArcherTower3, { 586, 197 });
		//	towerBuildCheck = !towerBuildCheck;
		//}
		//else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
		//{
		//	BuildTower(Tower::Types::WizardTower1, { 586, 197 });
		//	towerBuildCheck = !towerBuildCheck;

		//}
		//else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
		//{
		//	BuildTower(Tower::Types::WizardTower2, { 586, 197 });
		//	towerBuildCheck = !towerBuildCheck;
		//}
		//else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
		//{
		//	BuildTower(Tower::Types::WizardTower3, { 586, 197 });
		//	towerBuildCheck = !towerBuildCheck;
		//}
		//

		////if (INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
		////{
		////	towerBuildCheck = !towerBuildCheck;;
		////}



		//{
		//	diaBounds = diamond2.getGlobalBounds();
		//	isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		//	if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
		//		&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		//	{
		//		std::cout << "충돌체크2" << std::endl;
		//	}
		//	if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		//	{
		//		BuildTower(Tower::Types::ArcherTower1, { 857, 248 });
		//		//towerBuildCheck = !towerBuildCheck;
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		//	{
		//		BuildTower(Tower::Types::ArcherTower2, { 857, 248 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
		//	{
		//		BuildTower(Tower::Types::ArcherTower3, { 857, 248 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
		//	{
		//		BuildTower(Tower::Types::WizardTower1, { 857, 248 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
		//	{
		//		BuildTower(Tower::Types::WizardTower2, { 857, 248 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
		//	{
		//		BuildTower(Tower::Types::WizardTower3, { 857, 248 });

		//	}
		//}

		//{
		//	diaBounds = diamond3.getGlobalBounds();
		//	isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		//	if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
		//		&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		//	{
		//		std::cout << "충돌체크3" << std::endl;
		//	}
		//	if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		//	{
		//		BuildTower(Tower::Types::ArcherTower1, { 632, 376 });
		//		//towerBuildCheck = !towerBuildCheck;
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		//	{
		//		BuildTower(Tower::Types::ArcherTower2, { 632, 376 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
		//	{
		//		BuildTower(Tower::Types::ArcherTower3, { 632, 376 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
		//	{
		//		BuildTower(Tower::Types::WizardTower1, { 632, 376 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
		//	{
		//		BuildTower(Tower::Types::WizardTower2, { 632, 376 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
		//	{
		//		BuildTower(Tower::Types::WizardTower3, { 632, 376 });

		//	}
		//}

		//{
		//	diaBounds = diamond4.getGlobalBounds();
		//	isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		//	if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
		//		&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		//	{
		//		std::cout << "충돌체크4" << std::endl;
		//	}
		//	if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		//	{
		//		BuildTower(Tower::Types::ArcherTower1, { 902, 428 });
		//		//towerBuildCheck = !towerBuildCheck;
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		//	{
		//		BuildTower(Tower::Types::ArcherTower2, { 902, 428 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
		//	{
		//		BuildTower(Tower::Types::ArcherTower3, { 902, 428 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
		//	{
		//		BuildTower(Tower::Types::WizardTower1, { 902, 428 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
		//	{
		//		BuildTower(Tower::Types::WizardTower2, { 902, 4285 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
		//	{
		//		BuildTower(Tower::Types::WizardTower3, { 902, 428 });

		//	}
		//}

		//{
		//	diaBounds = diamond5.getGlobalBounds();
		//	isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		//	if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
		//		&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		//	{
		//		std::cout << "충돌체크5" << std::endl;
		//	}
		//	if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		//	{
		//		BuildTower(Tower::Types::ArcherTower1, { 767, 505 });
		//		//towerBuildCheck = !towerBuildCheck;
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		//	{
		//		BuildTower(Tower::Types::ArcherTower2, { 767, 505 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
		//	{
		//		BuildTower(Tower::Types::ArcherTower3, { 767, 505 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
		//	{
		//		BuildTower(Tower::Types::WizardTower1, { 767, 505 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
		//	{
		//		BuildTower(Tower::Types::WizardTower2, { 767, 505 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
		//	{
		//		BuildTower(Tower::Types::WizardTower3, { 767, 505 });

		//	}
		//}

		//{
		//	diaBounds = diamond6.getGlobalBounds();
		//	isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		//	if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
		//		&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		//	{
		//		std::cout << "충돌체크6" << std::endl;
		//	}
		//	if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
		//	{
		//		BuildTower(Tower::Types::ArcherTower1, { 1082, 479 });
		//		//towerBuildCheck = !towerBuildCheck;
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
		//	{
		//		BuildTower(Tower::Types::ArcherTower2, { 1082, 479 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num3))
		//	{
		//		BuildTower(Tower::Types::ArcherTower3, { 1082, 479 });
		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num4))
		//	{
		//		BuildTower(Tower::Types::WizardTower1, { 1082, 479 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
		//	{
		//		BuildTower(Tower::Types::WizardTower2, { 1082, 479 });

		//	}
		//	else if (!towerBuildCheck && INPUT_MGR.GetKeyDown(sf::Keyboard::Num6))
		//	{
		//		BuildTower(Tower::Types::WizardTower3, { 1082, 479 });

		//	}
		//}

	
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

void SceneDev1::SpawnEnemys(int count, sf::Vector2f pos) // 레디우스
{
	for (int i = 0; i < count; ++i)
	{
		Enemy* enemy = enemyPool.Get();
		enemy->SetPosition(352,-10);
		AddGo(enemy);
	}
}

void SceneDev1::OnDieEnemy(Enemy* enemy)
{
	SoundGo* findSound = (SoundGo*)FindGo("EnemyDie"); // 뿅소리
	findSound->sound.play();

	gold += 10;

	TextGo* findGo = (TextGo*)FindGo("Gold");

	std::stringstream message;
	message << "Gold:" << gold;
	findGo->text.setString(message.str());
	findGo->text.setFillColor(sf::Color::White);

	// 돈 떨어지는거 만드려면 AddGo(GoldEffect) 이런거 추가하기

	RemoveGo(enemy);
	enemyPool.Return(enemy);

	// 화살이랑 불렛 이펙트 2개
	// 신게임참고

	//SpriteEffect* bloodE = bloodEffectPool.Get(); 
	//bloodE->SetPosition(zombie->GetPosition());
	//AddGo(bloodE);
	//float bloodsize = 0.5 + (1.0 - ((int)zombie->GetType() * 0.5));
	//float rot = Utils::RandomRange(0, 270);
	//bloodE->SetSize(bloodsize, bloodsize);
	//bloodE->sprite.setRotation(rot);
	//bloodE->sprite.setRotation(rot);

	//SpriteEffect* bloodE = bloodEffectPool.Get();
	//bloodE->SetPosition(zombie->GetPosition());
	//AddGo(bloodE);
	//float bloodsize = 0.5 + (1.0 - ((int)zombie->GetType() * 0.5));
	//float rot = Utils::RandomRange(0, 270);
	//bloodE->SetSize(bloodsize, bloodsize);
	//bloodE->sprite.setRotation(rot);
	//bloodE->sprite.setRotation(rot);


	// 여기서 몬스터 돈 처리 (라운드 or 스테이지 및 몬스터 하나당)
	// 웨이브, 라운드, 돈 등 텍스트고 생각중

	// 월드 포지션을 타일인덱스로 변환하면
	// 나중에 마우스클릭 충돌처리도 할필요없다
}

void SceneDev1::EnemyEndPoint(Enemy* enemy)
{
	RemoveGo(enemy);
	enemyPool.Return(enemy);
}

//void SceneDev1::SetPosition(float x, float y)
//{
//	SpriteGo::SetPosition(x, y);
//}
//
//void SceneDev1::SetPosition(const sf::Vector2f& p)
//{
//	SpriteGo::SetPosition(p);
//}

void SceneDev1::BuildTower(Tower::Types towerType, sf::Vector2f pos)
{
	Tower* tower = towerPool.Get();
	tower->SetType(towerType);
	tower->SetPosition(pos);
	tower->Reset();
	AddGo(tower);

}

void SceneDev1::Test()
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		SpawnEnemys(1, {0,0});
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::C))
	{
		ClearObjectPool(enemyPool);
		ClearObjectPool(towerPool);
	}

	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	//{
	//	BuildTower(Tower::Types::ArcherTower2, { 561, 134 });
	//}


	


	/*{
		diaBounds = diamond3.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			Tower tower;
			animation.Play("Archer_Tower");
			tower.SetPosition(607, 313);

			std::cout << "충돌체크3" << std::endl;
		}
	}

	{
		diaBounds = diamond4.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(877, 365);

			std::cout << "충돌체크4" << std::endl;
		}
	}

	{
		diaBounds = diamond5.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(742, 442);

			std::cout << "충돌체크5" << std::endl;
		}
	}

	{
		diaBounds = diamond6.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(1057, 416);

			std::cout << "충돌체크6" << std::endl;
		}
	}*/


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
