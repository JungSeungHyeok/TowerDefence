#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "TileMap.h"

#include "InputMgr.h"

#include "SoundGo.h"
#include "SpriteEffect.h"

#include "Enemy.h"
#include "Tower.h"
#include "Arrow.h"



SceneDev1::SceneDev1() : Scene(SceneId::Dev1), tower(nullptr)
{
	resourceListPath = "scripts/SceneDev1ResourceList.csv";
}

void SceneDev1::Init()
{
	Release();

	sf::Vector2f size = FRAMEWORK.GetWindowSize();

	// 오브젝트 추가
	SpriteGo* background = (SpriteGo*)AddGo(new SpriteGo("Ui/guidebackgrund.png", "Back Ground"));
	background->SetOrigin(Origins::MC);
	background->sortLayer = 1;
	background->SetPosition(size.x / 2, size.y / 2);

	TextGo* goldText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Scene Name"));
	goldText->sortLayer = 100;
	goldText->text.setCharacterSize(23);
	goldText->text.setFillColor(sf::Color::Yellow);
	goldText->text.setString(L"Gold: 320"); // 임시값
	goldText->SetPosition(75, 15);

	TextGo* waveText = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Scene Name"));
	waveText->sortLayer = 100;
	waveText->text.setCharacterSize(23);
	waveText->text.setFillColor(sf::Color::White);
	waveText->text.setString(L"Wave 1/5"); // 임시값
	waveText->SetPosition(75, 65);

	TextGo* gold = (TextGo*)AddGo(new TextGo("fonts/CookieRunRegular.ttf", "Scene Name"));
	gold->sortLayer = 100;
	gold->text.setCharacterSize(23);
	gold->text.setFillColor(sf::Color::Red);
	gold->text.setString(L"Life: 15"); // 임시값
	gold->SetPosition(75, 115);


	tileMap = (TileMap*)AddGo(new TileMap("graphics/grass.png", "Tile Map"));

	// 몬스터 오브젝트풀

	enemyPool.OnCreate = [this](Enemy* enemy)
	{
		Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 1);
		enemy->SetType(enemyType);
	};
	enemyPool.Init();

	// 애로우 오브젝트풀

	arrowPool.OnCreate = [this](Arrow* arrow)
	{
		arrow->GetArrowPool(&arrowPool);
		Arrow::Types arrowType = (Arrow::Types)Utils::RandomRange(0, Arrow::TotalTypes - 1);
		arrow->SetType(arrowType);
	};
	arrowPool.Init();

	// 타워 오브젝트풀

	towerPool.OnCreate = [this](Tower* tower) {
		tower->GetArrowPool(&arrowPool);
	};
	towerPool.Init();

	// 오브젝트 오브젝트풀

	objectPool.OnCreate = [this](Object* object)
	{
		Object::Types objectType = (Object::Types)Utils::RandomRange(0, Object::TotalTypes - 1);
		object->SetType(objectType);
	};
	objectPool.Init();


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
	


	//
	//for (int i = 0; i < 5; i++)
	//{
	//	Object* object = objectPool.Get();
	//	object->SetPosition(objPos.x * (i), objPos.y);
	//	objPos.x += 51;
	//}
	//
	//AddGo(object);





	//sf::Vector2f startPos = { 45, 56 };
	//float heightDifference = objPos.y * 0.3025f;

	//for (int i = 0; i < 3; ++i)
	//{
	//	Object* object = objectPool.Get();
	//	object->SetPosition(objPos.x, objPos.y * i);

	//	if (i % 10 == 0)
	//	{
	//		//break;
	//	}

	//	//objPos.x += 80;
	//	//objPos.y += 50;
	//	AddGo(object);
	//}


}

void SceneDev1::SpawnEnemys(int count, sf::Vector2f pos) // 레디우스
{
	for (int i = 0; i < count; ++i)
	{
		Enemy* enemy = enemyPool.Get();
		enemy->SetPosition(352, -10);
		AddGo(enemy);
	}
}

void SceneDev1::OnDieEnemy(Enemy* enemy)
{
	SoundGo* findSound = (SoundGo*)FindGo("EnemyDie"); // 뿅소리
	//findSound->sound.play();

	// gold += 10;

	TextGo* findGo = (TextGo*)FindGo("Gold");

	/*std::stringstream message;
	message << "Gold:" << gold;
	findGo->text.setString(message.str());
	findGo->text.setFillColor(sf::Color::White);*/

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

const std::list<Enemy*>* SceneDev1::GetEnemyList() const
{
	return &enemyPool.GetUseList();
}

const std::list<Tower*>* SceneDev1::GetTowerList() const
{
	return &towerPool.GetUseList();
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






void SceneDev1::TowerAttack()
{





	// 오브젝트풀은 몬스터, 타워, 화살 모두 썼다.
	// 체력, 데미지, 스피드 등은 모두 csv 엑셀 파일에 명시되어있다.
	// 타워 -> 애니미리스트 들고있음
	// 
	// 애로우 -> 애니미리스트 이것도 되긴하는데 방식이다름
	// 
	// 애니미 -> 애로우리스트(불렛)

	// 1. 애로우는 타워의 겟포지션에서 출발한다.
	// 2. 애로우의 목적지는 몬스터의 겟 포지션이다.
	// 3. 애로우는 몬스터의 포지션과 겹치면 사라진다.

	//Arrow* arrow = arrowPool.Get();
	
	
	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::A))
	//{
	//	std::cout << "Test A키" << std::endl;
	//	//arrow->SetPosition(500, 300);
	//	//arrow->Reset();
	//	arrow->Aiming(position, look, 1000.f);
	//	AddGo(arrow);
	//}


	//float distance = Utils::Distance(this->tower->sprite.getPosition(), this->enemy->sprite.getPosition());

	// 1. 
	

	 // csv값 정보 받아서 적용


	//arrow->SetType(arrowType);
	//arrow->SetPosition(pos);
	//arrow->Reset();


	
	//	arrow->Aiming(); // 인자 3개0


}



void SceneDev1::BuildTower(Tower::Types towerType, sf::Vector2f pos)
{
	Tower* tower = towerPool.Get();
	tower->SetType(towerType);
	tower->SetPosition(pos);
	tower->Reset();
	AddGo(tower);

	std::cout << tower->GetPosition().x << " , " << tower->GetPosition().y << std::endl;
}

void SceneDev1::SpawnArrows(/*Arrow::Types arrowType, */int count, sf::Vector2f pos)
{

	//Arrow* arrow = arrowPool.Get();
	//arrow->SetType(arrowType);
	//arrow->SetPosition(pos);
	//arrow->Reset();
	//AddGo(arrow);


	//for (int i = 0; i < count; ++i)
	//{
	//	Arrow* arrow = arrowPool.Get();
	//	arrow->SetPosition(352, 200);
	//	AddGo(arrow);
	//}

}

void SceneDev1::Test()
{


	//sf::Vector2f popo;
	//sf::Vector2f loooook;
	//TowerAttack(popo, loooook, 10.f);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::E))
	{
		SpawnEnemys(1, {0,0});
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
		//sf::Vector2f objDir = { 300, 400 };

		BuildObject(25, { 0,0 });

		//for (int i = 0; i < 20; i++)
		//{
		//	BuildObject(1, { 0,0 });
		//	//objDir.y += 80;
		//}

		std::cout << "오브젝트 생성!" << std::endl;
	}

	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::A))
	//{
	//	SpawnArrows(1, { 0,0 });
	//	std::cout << "화살 생성!" << std::endl;
	//}


	/*if (INPUT_MGR.GetKeyDown(sf::Keyboard::A))
	{
		Arrow* arrow = arrowPool.Get();
		arrow->Aiming({ 0,0 }, {0, 0}, 1000.f);

		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
		if (sceneDev1 != nullptr)
		{
			arrow->SetEnemyList(sceneDev1->GetEnemyList());
			sceneDev1->AddGo(arrow);
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
