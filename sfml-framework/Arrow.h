#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"

class Enemy;

class Arrow : public SpriteGo
{

public:
	enum class Types
	{
		Arrow, // ȭ��
		Wizard_Bullet, // ��
	};
	static const int TotalTypes = 2;

protected:
	Types arrowType;

	sf::Vector2f direction;
	float speed;
	float range;
	int damage;

	const std::list<Enemy*>* enemys;

	// const Tower::Types* towerType; �ٽú���

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

	void SetRange(float range);
	void SetArrowSpeed(float speed);
	void SetDamage(int damage);

	//void Aiming(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed); // ���� ���� ���̾�

	void SetEnemyList(const std::list<Enemy*>* list); // ���� ����Ʈ


	//Enemy* MostCloseEnemy();


};

