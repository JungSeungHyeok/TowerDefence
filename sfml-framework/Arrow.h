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

	// const Tower::Types* towerType; �ٽú���

public:
	ObjectPool<Arrow>* pool;

	Arrow(const std::string& textureId = "", const std::string& n = "");
	virtual ~Arrow() override;

	void SetEnemyList(const std::list<Enemy*>* list); // ���� ����Ʈ

	void Aiming(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed); // ���� ���� ���̾�

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	Enemy* MostCloseEnemy(Enemy* enemy);


};

