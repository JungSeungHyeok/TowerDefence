#pragma once
#include "Scene.h"
#include "ObjectPool.h"
#include "AnimationController.h"
#include <sstream>
#include "Tower.h"
#include "SpriteGo.h"


class Enemy;

// class ��������Ʈ ����Ʈ
class TileMap;

class SceneDev1 : public Scene
{
protected:
	AnimationController animation;
	TileMap* tileMap = nullptr;
	Enemy* enemy = nullptr;
	Tower* tower = nullptr;

	ObjectPool<Enemy> enemyPool;
	ObjectPool<Tower> towerPool;

	bool isInstalled = false;
	bool testHide = true;

	sf::ConvexShape diamond1;
	sf::ConvexShape diamond2;
	sf::ConvexShape diamond3;
	sf::ConvexShape diamond4;
	sf::ConvexShape diamond5;
	sf::ConvexShape diamond6;
	sf::FloatRect diaBounds;

	const float diamondWidth = 35.f;
	const float diamondHeight = 35.f; // ������ ũ��

	bool towerBuildCheck1 = true;
	bool towerBuildCheck2 = true;
	bool towerBuildCheck3 = true;
	bool towerBuildCheck4 = true;
	bool towerBuildCheck5 = true;
	bool towerBuildCheck6 = true;

	sf::FloatRect enemyBounds; // �浹üũ
	bool GameOver = false;

	//int tileHei = 0;
	//int tileWid = 0;

	int round = 0;
	int stage = 0;
	int gold = 0;
	
	int frame = 0; // ������ üũ �ð�����
	float totalDt = 0;
	bool frameCheck = false;

public:
	SceneDev1();
	virtual ~SceneDev1() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	template <typename T>
	void ClearObjectPool(ObjectPool<T>& pool);

	// ���� ���� ����
	void StartGame();
	void StartRound();
	void EndRound();
	void StartStage();
	void EndStage();
	void SaveFile();

	// ���� ����
	void SpawnEnemys(int count, sf::Vector2f pos); // ����콺
	void OnDieEnemy(Enemy* enemy);
	void EnemyEndPoint(Enemy* enemy);

	// Ÿ�� ���� , �������ǵ� �߰�
	/*virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);*/


	void BuildTower(Tower::Types towerType, sf::Vector2f pos);


	/*void BuildTower(Tower::Types type);*/






	void Test();


	// sf::Vector2f screenToIsoTileCoords(sf::Vector2f screenCoords, sf::Vector2f tile);
	// Ÿ�ϸ����� �ű�
};

template<typename T>
inline void SceneDev1::ClearObjectPool(ObjectPool<T>& pool)
{
	for (auto object : pool.GetUseList())
	{
		RemoveGo(object);
	}
	pool.Clear();
}

