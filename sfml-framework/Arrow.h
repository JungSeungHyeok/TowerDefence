#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"


class Enemy;

class Arrow : public SpriteGo
{

public:
	enum class Types
	{
		Arrow, // 화살
		Wizard_Bullet, // 구
	};
	static const int TotalTypes = 2;

protected:
	Types arrowType;
	Tower* tower = nullptr;
	Enemy* enemy = nullptr;

	float attackTime = 0.0f;
	float targetTime = 1.f;

	//ObjectPool<Enemy> enemyPool;

	sf::Vector2f position;
	sf::Vector2f direction;
	float speed = 0;
	float range = 0;
	int damage = 0;

	const std::list<Enemy*>* enemys = nullptr;

	// const Tower::Types* towerType; 다시보기

public:
	ObjectPool<Arrow>* arrowPool = nullptr;

	Arrow(const std::string& textureId = "", const std::string& n = "")
		:SpriteGo(textureId, n) {}
	virtual ~Arrow() override { Release(); };
	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	bool Load(const std::string& filePath);
	void SetType(Types t);
	Types GetType() const;

	void GetArrowPool(ObjectPool<Arrow>* pool)
	{
		this->arrowPool = pool;
	}

	void Aiming(sf::Vector2f pos, sf::Vector2f direction, float speed, float range, int damage); // 포즈, 디렉션, 스피드 등 포즈를 넘기기
		
		//float range, float speed, int damage, sf::Vector2f direction);
		
	void SetEnemyList(const std::list<Enemy*>* list);

};

