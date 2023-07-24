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

	sf::Vector2f direction;
	float speed;
	float range;
	int damage;

	const std::list<Enemy*>* enemys = nullptr;

	// const Tower::Types* towerType; 다시보기

public:
	ObjectPool<Arrow>* pool;

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

	void Aiming(float range, float speed, int damage, sf::Vector2f direction);
	void SetEnemyList(const std::list<Enemy*>* list);

};

