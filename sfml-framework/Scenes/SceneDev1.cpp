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

	// csv�� ���� �ִϸ��̼Ǹ� �߰��ϰ�
	// Ÿ�� �⺻ �̹����� ��������Ʈ png �׳� �����ڰ�
	// csv�� ���� �ִϸ��̼Ǹ� �߰��ϰ�
	// Ÿ�� �⺻ �̹����� ��������Ʈ png �׳� �����ڰ�
}

void SceneDev1::Init()
{
	Release();

	sf::Vector2f size = FRAMEWORK.GetWindowSize();

	TextGo* sceneName = (TextGo*)AddGo(new TextGo("", "Scene Name"));
	sceneName->sortLayer = 100;
	sceneName->text.setCharacterSize(25);
	sceneName->text.setFillColor(sf::Color::White);
	sceneName->text.setString(L"Ÿ�����潺");

	tileMap = (TileMap*)AddGo(new TileMap("graphics/grass.png", "Tile Map"));



	//AddGo(new TileMap("Object/crystal(3).png", "Tile Map"));

	//AddGo(new TileMap("graphics/grass.png", "Tile Map"));





	tower = (Tower*)AddGo(new Tower("Tower/Archer/archer_level_1.png", "ArcherTower"));

	// Tower* tower = (Tower*)AddGo(new Tower());

	/*tower = (Tower*)AddGo(new Tower("Towers/Archer/archer_level_1.png", "Tower"));



	
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetPosition(size * 0.5f);
	tileMap->sortOrder = 1;*/



	// enemy->�ε����� �浹�Լ�


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





	//std::cout << "���콺x: " << uiMousePos.x << "���콺y: "<< uiMousePos.y << std::endl;

	// �׽�Ʈ

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


		// ���Ⱑ �̺�Ʈ ó�� �κ�
		// Ÿ�� ��ġ �ϰ� ������ ����� �ϸ� ��
		// Ÿ������ �Ҽ��� ���� �ϴ� �׽�Ʈ�ڵ�



	
		// �̹� Ÿ�� �̴ֿ��� �����ϱ� 
		
		//tower->InstallTower(isoTileCoords, tileSize);

		/*tower->SetPosition(isoTileCoords.x * tileSize.x, isoTileCoords.y * tileSize.y);*/

		//isInstalled = true;



		//if (!isInstalled)
		//{ // �̹� Ÿ���� ��ġ���� ���� Ÿ���� ��쿡�� ��ġ

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
		//tower->SetActive(true); //  �̰� �ϸ� ������
		




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

void SceneDev1::SpawnEnemys(int count, sf::Vector2f pos) // ����콺
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
	SoundGo* findSound = (SoundGo*)FindGo("EnemyDie"); // �мҸ�
	findSound->sound.play();

	// ȭ���̶� �ҷ� ����Ʈ 2��
	// �Ű�������

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


	// ���⼭ ���� �� ó�� (���� or �������� �� ���� �ϳ���)
	// ���̺�, ����, �� �� �ؽ�Ʈ�� ������

	// ���� �������� Ÿ���ε����� ��ȯ�ϸ�
	// ���߿� ���콺Ŭ�� �浹ó���� ���ʿ����
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



//// �׽�Ʈ
//
//sf::Vector2f SceneDev1::screenToIsoTileCoords(sf::Vector2f screenCoords, sf::Vector2f tile)
//{
//	//sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//	//screenCoords = sf::Mouse::getPosition(window);
//	// ���̼Ҹ�Ʈ�� Ÿ�� ũ�� ����
//	//sf::Vector2f testTile = { 90 , 85};
//
//	/*const int tileWid = 90;
//	const int tileHei = 85;*/
//
//	// Ÿ�ϸ� ũ�� ����
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
