#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"

class Enemy;

class Arrow : public SpriteGo
{

protected:

	sf::Vector2f direction;
	float speed = 0.f;
	float range = 0.f;
	int damage = 0;

	const std::list<Enemy*>* enemys;

	// const Tower::Types* towerType; 다시보기

public:
	ObjectPool<Arrow>* pool;

	Arrow(const std::string& textureId = "", const std::string& n = "");
	virtual ~Arrow() override;

	void SetEnemyList(const std::list<Enemy*>* list); // 몬스터 리스트

	void Aiming(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed); // 조준 기존 파이어

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	Enemy* MostCloseEnemy(Enemy* enemy);


};

