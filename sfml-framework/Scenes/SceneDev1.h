#pragma once
#include "Scene.h"
#include "ObjectPool.h"
#include "AnimationController.h"
#include <sstream>
#include "Tower.h"
#include "SpriteGo.h"
#include "TowerTable.h"
#include "Object.h"
#include "TextGo.h"
#include "UIButton.h"
#include "DataTableMgr.h"

class Enemy;
class Arrow;
// class 스프라이트 이펙트
class TileMap;
class SpriteEffect;

class SceneDev1 : public Scene
{
protected:

	// std::map<std::string, bool> mouseOverStates; // ui 버튼 추가시 주석 제거
	sf::Sprite background;
	
	UIButton* giveupButton;
	SpriteGo* roundStart;
	SpriteGo* pauseBoard;
	SpriteGo* upgradeArcher2;
	//UIButton* pauseButton;
	//UIButton* volumeOnButton;
	//UIButton* volumeOffButton;

	//sf::Sprite roundStart;

	float targetDuration = 2.0f;
	float trigger = 0.0f;


	sf::Vector2f currentPosition = { 640, 400 };
	sf::Vector2f targetPosition = { 1241, 33 };

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
	ObjectPool<SpriteEffect> goldEffectPool;

	const std::list<Enemy*>* enemys;

	// std::list<Enemy> enemys;

	bool isInstalled = false;
	bool testHide = false;

	// 라운드, 스테이지 등
	bool isRoundStart = false;
	int roundCheck = 1; // 1라운드, 2라운드 ....
	int roundTotalEnemy = 0;
	int roundCountEnemy = 35;
	float enemytrigger = 0.0f;
	float raceMode = 0.0f;
	int reaceModeCount = 5;


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

	bool towerUpgradeCheck1 = false;
	bool towerUpgradeCheck2 = false;
	bool towerUpgradeCheck3 = false;
	bool towerUpgradeCheck4 = false;
	bool towerUpgradeCheck5 = false;
	bool towerUpgradeCheck6 = false;

	sf::FloatRect enemyBounds; // 충돌체크


	bool GameOver = false;


	TextGo* lifeText;
	TextGo* goldText;
	TextGo* waveText;
	TextGo* upgradeText;

	int life = 15;
	int gold = 320;
	int wave = 1;
	
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
	void SetEnemyList(const std::list<Enemy*>* list); // 추가
	void SpawnEnemys(int enemyCount, Enemy::Types type); // 레디우스
	void OnDieEnemy(Enemy* enemy);
	void EnemyEndPoint(Enemy* enemy);

	
	const std::list<Tower*>* GetTowerList() const;
	const std::list<Enemy*>* GetEnemyList() const;
	const std::list<Arrow*>* GetArrowList() const;

	// 타워 관련 , 셋포지션도 추가
	//void TowerAttack();
	void BuildTower(Tower::Types towerType, sf::Vector2f pos);
	void UpdateGold(int amount);

	void Test();

	void ResetGame();

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

