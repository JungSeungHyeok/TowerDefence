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
// class ��������Ʈ ����Ʈ
class TileMap;
class SpriteEffect;

class SceneDev1 : public Scene
{
protected:

	int life = 15;
	int gold = 320;
	int wave = 1;

	// ����, �������� ��
	bool isRoundStart = false;
	int roundCheck = 1; // 1����, 2���� ....
	int roundTotalEnemy = 0;
	int roundCountEnemy = 20;
	float enemytrigger = 0.0f;
	float raceMode = 0.0f;
	int reaceModeCount = 1;
	
	sf::Sprite background;
	UIButton* giveupButton;
	SpriteGo* roundStart;
	SpriteGo* pauseBoard;

	SpriteGo* basicArcher;
	SpriteGo* upgradeArcher2;
	SpriteGo* upgradeArcher3;

	//UIButton* pauseButton;
	//UIButton* volumeOnButton;
	//UIButton* volumeOffButton;
	// std::map<std::string, bool> mouseOverStates; // ui ��ư �߰��� �ּ� ����
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

	sf::ConvexShape diamond1;
	sf::ConvexShape diamond2;
	sf::ConvexShape diamond3;
	sf::ConvexShape diamond4;
	sf::ConvexShape diamond5;
	sf::ConvexShape diamond6;
	sf::FloatRect diaBounds;

	const float diamondWidth = 35.f;
	const float diamondHeight = 35.f; // ������ ũ��

	bool towerUpgradeCheck1 = true;
	bool towerUpgradeCheck2 = true;
	bool towerUpgradeCheck3 = true;
	bool towerUpgradeCheck4 = true;
	bool towerUpgradeCheck5 = true;
	bool towerUpgradeCheck6 = true;

	bool towerbuildComplete1 = true;
	bool towerbuildComplete2 = true;
	bool towerbuildComplete3 = true;
	bool towerbuildComplete4 = true;
	bool towerbuildComplete5 = true;
	bool towerbuildComplete6 = true;

	bool towerUpgradeComplete1 = false;
	bool towerUpgradeComplete2 = false;
	bool towerUpgradeComplete3 = false;
	bool towerUpgradeComplete4 = false;
	bool towerUpgradeComplete5 = false;
	bool towerUpgradeComplete6 = false;


	sf::FloatRect enemyBounds; // �浹üũ


	bool GameOver = false;


	TextGo* lifeText;
	TextGo* goldText;
	TextGo* waveText;
	TextGo* buyText;

	TextGo* basicText;
	TextGo* upgradeText2;
	TextGo* upgradeText3;


	
	int frame = 0; // ������ üũ �ð�����
	float totalDt = 0;
	bool frameCheck = false;

	SpriteGo goldCoin;
	AnimationController goldAnimation;

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

	// ������Ʈ ����

	void BuildObject(int count, sf::Vector2f pos);

	// ���� ����
	void SetEnemyList(const std::list<Enemy*>* list); // �߰�
	void SpawnEnemys(int enemyCount, Enemy::Types type); // ����콺
	void OnDieEnemy(Enemy* enemy);
	void EnemyEndPoint(Enemy* enemy);

	
	const std::list<Tower*>* GetTowerList() const;
	const std::list<Enemy*>* GetEnemyList() const;
	const std::list<Arrow*>* GetArrowList() const;

	// Ÿ�� ���� , �������ǵ� �߰�
	//void TowerAttack();
	void BuildTower(Tower::Types towerType, sf::Vector2f pos);
	void BuildUpgradeTower(Tower::Types towerType, sf::Vector2f pos);
	void BuildUpgradeTower2(Tower::Types towerType, sf::Vector2f pos);
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

