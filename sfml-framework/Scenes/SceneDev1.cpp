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



	//AddGo(new TileMap("Object/crystal(3).png", "Tile Map"));

	//AddGo(new TileMap("graphics/grass.png", "Tile Map"));





	tower = (Tower*)AddGo(new Tower("Tower/Archer/archer_level_1.png", "ArcherTower"));

	// Tower* tower = (Tower*)AddGo(new Tower());

	/*tower = (Tower*)AddGo(new Tower("Towers/Archer/archer_level_1.png", "Tower"));



	
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetPosition(size * 0.5f);
	tileMap->sortOrder = 1;*/



	// enemy->부딪히는 충돌함수


	enemyPool.OnCreate = [this](Enemy* enemy) {
		Enemy::Types enemyType = (Enemy::Types)Utils::RandomRange(0, Enemy::TotalTypes - 1);
		enemy->SetType(enemyType);
	};
	enemyPool.Init();

	//enemy->sortLayer = 100;

	for (auto go : gameObjects)
	{
		go->Init();
	}

	tower->SetOrigin(Origins::MC);
	tower->SetPosition(-500, 200);
	tower->sortLayer = 5;

	tileMap->Load("map/map2.csv");
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetPosition(size * 0.5f);
	tileMap->sortOrder = -1;

	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(size * 0.5f);
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


	Test();

	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = ScreenToUiPos(mousePos);





	//std::cout << "마우스x: " << uiMousePos.x << "마우스y: "<< uiMousePos.y << std::endl;

	// 테스트

	bool isHover = false;
	bool prevHover = isHover;


	//if (!prevHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Right))
	//{
	//	//tower->Load(".csv");



	//	tower->SetOrigin(Origins::MC);
	//	tower->SetPosition(0, 200);
	//	tower->sortLayer = 5;

	//	//tower = new Tower();
	//	////tower->SetOrigin(Origins::MC);
	//	//tower->SetPosition(500, 500);
	//	//AddGo(tower);
	//	std::cout << "test...." << std::endl;

	//}



	if (!prevHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f tileSize = {90, 85};

		// sf::Vector2f tileSize = {90, 25.71f};

		/*sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2i isoTileCoords = screenToIsoTileCoords(mousePosition, tileSize.x, tileSize.y);*/
		TileMap tile;

		sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
		sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

		sf::Vector2f isoTileCoords = tile.screenToIsoTileCoords(uiMousePos, sf::Vector2f (tileSize.x, tileSize.y));
			

		std::cout << "Clicked Isometric Tile: (" << isoTileCoords.x << ", " << isoTileCoords.y << ")" << std::endl;


		// 여기가 이벤트 처리 부분
		// 타워 설치 하고 싶으면 여기다 하면 됨
		// 타워에다 할수도 있음 일단 테스트코드



	
		// 이미 타워 이닛에서 했으니까 
		
		//tower->InstallTower(isoTileCoords, tileSize);

		/*tower->SetPosition(isoTileCoords.x * tileSize.x, isoTileCoords.y * tileSize.y);*/

		//isInstalled = true;



		//if (!isInstalled)
		//{ // 이미 타워가 설치되지 않은 타일인 경우에만 설치

		//	if (tower == nullptr)
		//	{
		//		tower = new Tower();
		//		tower->InstallTower(isoTileCoords, tileSize);
		//		AddGo(tower);
		//	}



		//	
		//}

	

		/*tower->GetSize();
		tower->GetCenter();
		animation.Play("Idle");*/
		//tower->SetOrigin(Origins::MC);
		//tower->SetActive(true); //  이거 하면 오류남
		




		//std::cout << "tileSize: " << tileSize.x << ", " << tileSize.y << std::endl;


	}




	//isHover = sprite.getGlobalBounds().contains(uiMousePos);

	//if (!prevHover && isHover)
	//{
	//	if (OnEnter != nullptr)
	//		OnEnter();
	//}
	//if (prevHover && !isHover)
	//{
	//	if (OnExit != nullptr)
	//		OnExit();
	//}
	//if (isHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	//{
	//	if (OnClick != nullptr)
	//		OnClick();
	//}


	//if (INPUT_MGR.GetKeyDown(sf::Mou))
	//{

	//}





	//	enemy->SetPosition(uiMousePos);


	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num5))
	//{
	//	Test();
	//}
	
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
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

void SceneDev1::SpawnEnemys(int count, sf::Vector2f pos) // 레디우스
{
	for (int i = 0; i < count; ++i)
	{
		Enemy* enemy = enemyPool.Get();
		enemy->SetPosition(332,-1);

		AddGo(enemy);



		//sf::Vector2f size = FRAMEWORK.GetWindowSize();
		//worldView.setSize(size);
		//worldView.setCenter(0, 0);
		//uiView.setSize(size);
		//uiView.setCenter(0, 0);

		//sf::Vector2f startPos;
		//sf::Vector2f currPos = startPos;
		
		/*sf::Vector2f mousePos;

		mousePos = (sf::Vector2f)sf::Mouse::getPosition(FRAMEWORK.GetWindow());*/



		
		/*bool prevHover = isHover;
		isHover = sprite.getGlobalBounds().contains(uiMousePos);*/
		

	/*	enemy->SetPosition(startPos -= {45, 45});
		enemy->SetPosition(startPos += {35, 25});*/

		//enemy->SetPosition({-415, -415 });
		//enemy->SetPosition({95, 95 });
		//enemy->SetPosition({-95, -59 });

	


		
	
		
	}
}

void SceneDev1::OnDieEnemy(Enemy* enemy)
{
	SoundGo* findSound = (SoundGo*)FindGo("EnemyDie"); // 뿅소리
	findSound->sound.play();

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

	// life--;


}

void SceneDev1::Test()
{
	sf::Vector2f center;
	
	center = FRAMEWORK.GetWindowSize() * 0.5f;

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		SpawnEnemys(1, { 0, 0 });
	
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	{
		ClearObjectPool(enemyPool);
	}

	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num2))
	//{
	//	ClearObjectPool(enemyPool);
	//}

}



//// 테스트
//
//sf::Vector2f SceneDev1::screenToIsoTileCoords(sf::Vector2f screenCoords, sf::Vector2f tile)
//{
//	//sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//	//screenCoords = sf::Mouse::getPosition(window);
//	// 아이소메트릭 타일 크기 설정
//	//sf::Vector2f testTile = { 90 , 85};
//
//	/*const int tileWid = 90;
//	const int tileHei = 85;*/
//
//	// 타일맵 크기 설정
//	//sf::Vector2f testTileMap = { 90 , 85 };
//
//	//const int tilesX = 90;
//	//const int tilesY = 85;
//
//	//float tileWidth = 0;
//	//float tileHeight = 0;
//
//
//	float tileXf = static_cast<float>(screenCoords.x) / tile.x - static_cast<float>(screenCoords.y) / tile.y;
//	float tileYf = static_cast<float>(screenCoords.x) / tile.x + static_cast<float>(screenCoords.y) / tile.y;
//
//	int tileX = static_cast<int>(tileXf);
//	int tileY = static_cast<int>(tileYf);
//
//	return sf::Vector2f(tileX, tileY);
//
//
//
//	/*float tileXf = static_cast<float>(screenCoords.x) / tileWid - static_cast<float>(screenCoords.y) / tileHei;
//	float tileYf = static_cast<float>(screenCoords.x) / tileWid + static_cast<float>(screenCoords.y) / tileHei;
//
//	int tileX = static_cast<int>(tileXf);
//	int tileY = static_cast<int>(tileYf);
//
//	return sf::Vector2i(screenCoords);*/
//}
