#pragma once
#include "Scene.h"
#include "ObjectPool.h"
#include "AnimationController.h"
#include <sstream>

class Tower;
class Enemy;

// class 스프라이트 이펙트
class TileMap;

class SceneDev1 : public Scene
{
protected:
	TileMap* tileMap = nullptr;
	Enemy* enemy = nullptr;
	Tower* tower = nullptr;
	ObjectPool<Enemy> enemyPool;
	// 스프라이트 이펙트 추후 
	AnimationController animation;

	bool isInstalled = false; // 타워 설치 가능한 타일인지 판단


	sf::FloatRect enemyBounds; // 충돌체크
	bool GameOver = false;

	//int tileHei = 0;
	//int tileWid = 0;

	int round = 0;
	int stage = 0;
	int money = 0;
	
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

	// 몬스터 관련
	void SpawnEnemys(int count, sf::Vector2f pos); // 레디우스

	void OnDieEnemy(Enemy* enemy);

	void EnemyEndPoint(Enemy* enemy);


	void Test();


	// sf::Vector2f screenToIsoTileCoords(sf::Vector2f screenCoords, sf::Vector2f tile);
	// 타일맵으로 옮김
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

