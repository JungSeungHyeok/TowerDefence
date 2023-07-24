#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "Enemy.h"
#include "ObjectPool.h"
#include "Arrow.h"
#include "EnemyTable.h"

// 타워도 스프라이트
// 애니메이션 상태 표현

class SoundGo;
class SceneDev1;
class GameObject;


class Tower : public SpriteGo
{
public:
	enum class Types
	{
		ArcherTower1,
		ArcherTower2,
		ArcherTower3,

		WizardTower1,
		WizardTower2,
		WizardTower3,
	};
	static const int TotalTypes = 6;


protected:
	AnimationController animation; // 추가
	Types towerType;

	ObjectPool<Arrow>* poolArrows;

	Tower* tower;
	Enemy* enemy;

	const std::list<Enemy*>* enemys;

	// 갖고 있을 필요가 있나

	//ObjectPool<Enemy> poolEnemys;
	

	sf::Vector2f direction; // 추가
	int damage;
	int range;
	float speed;

	float attackRate;
	float arrowSpeed;
	int price;


public:
	Tower(const std::string& textureId = "", const std::string& n = "")
		:SpriteGo(textureId, n) {}
	virtual ~Tower() override { Release(); };

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	bool Load(const std::string& filePath);

	void SetType(Types t);
	Types GetType() const;

	void SetEnemyList(const std::list<Enemy*>* list); // 필수1

	void GetSearchEnemy();

	void GetEnemy(Enemy* enemy);

	void LostEnemy();

	void GetArrowPool(ObjectPool<Arrow>* pool)
	{
		this->poolArrows = pool;
	}

	bool CheckEnemy() { return enemy != nullptr; }

	void TowerAttack();



	//sf::Vector2f GetSize(); // 사이즈 구하고
	//sf::Vector2f GetCenter(); // 타일 중앙에 설치하고

};

