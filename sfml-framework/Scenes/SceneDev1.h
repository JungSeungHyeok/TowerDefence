#pragma once
#include "Scene.h"
#include "ObjectPool.h"
#include "AnimationController.h"
#include <sstream>
#include "Tower.h"
#include "SpriteGo.h"
#include "TowerTable.h"
#include "Object.h"


class Enemy;
class Arrow;
// class 스프라이트 이펙트
class TileMap;

class SceneDev1 : public Scene
{
protected:
	AnimationController animation;
	TileMap* tileMap = nullptr;
	Enemy* enemy = nullptr;
	Tower* tower = nullptr;
	Arrow* arrow = nullptr;
	Object* object = nullptr;

	ObjectPool<Enemy> enemyPool;
	ObjectPool<Tower> towerPool;
	ObjectPool<Arrow> arrowPool;
	ObjectPool<Object> objectPool;

	const std::list<Enemy*>* enemys;

	// std::list<Enemy> enemys;

	bool isInstalled = false;
	bool testHide = false;


	sf::ConvexShape diamond1;
	sf::ConvexShape diamond2;
	sf::ConvexShape diamond3;
	sf::ConvexShape diamond4;
	sf::ConvexShape diamond5;
	sf::ConvexShape diamond6;
	sf::FloatRect diaBounds;
	
	const float diamondWidth = 35.f;
	const float diamondHeight = 35.f; // 마름모 크기

	bool towerBuildCheck1 = true;
	bool towerBuildCheck2 = true;
	bool towerBuildCheck3 = true;
	bool towerBuildCheck4 = true;
	bool towerBuildCheck5 = true;
	bool towerBuildCheck6 = true;

	sf::FloatRect enemyBounds; // 충돌체크
	bool GameOver = false;

	//int tileHei = 0;
	//int tileWid = 0;

	int round = 0;
	int stage = 0;
	int gold = 0;
	
	int frame = 0; // 프레임 체크 시간나면
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

	// 게임 시작 종료
	void StartGame();
	void StartRound();
	void EndRound();
	void StartStage();
	void EndStage();
	void SaveFile();

	// 오브젝트 관련

	void BuildObject(int count, sf::Vector2f pos);

	// 몬스터 관련
	void SpawnEnemys(int count, sf::Vector2f pos); // 레디우스
	void OnDieEnemy(Enemy* enemy);
	void EnemyEndPoint(Enemy* enemy);

	const std::list<Enemy*>* GetEnemyList() const;
	const std::list<Tower*>* GetTowerList() const;

	// 타워 관련 , 셋포지션도 추가
	void TowerAttack();

	void BuildTower(Tower::Types towerType, sf::Vector2f pos);

	void SpawnArrows(/*Arrow::Types arrowType, */int count, sf::Vector2f pos);

	void Test();

	




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

