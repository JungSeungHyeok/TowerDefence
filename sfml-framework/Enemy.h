#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

// ���� �浹 üũ�Ҷ� �̹��� ����� �ϱ�?

class Tower;
class SoundGo;

class Enemy: public SpriteGo
{
public:
	enum class Types
	{
		Ufo1,
		Ufo2,
		Ufo3,
		Ufo4,
		Ufo5,
		Ufo6,
		Ufo7,
	};
	static const int TotalTypes = 7;

protected:
	AnimationController animation;
	Types enemyType;
	const std::list<Tower*>* towers = nullptr;
	sf::Vector2f currPoint;

	sf::Vector2f point1 = { 855.f, 268.f };
	sf::Vector2f point2 = { 584.f, 422.f };
	sf::Vector2f point3 = { 764.f, 525.f };
	sf::Vector2f point4 = { 1034.f, 369.f };
	sf::Vector2f point5 = { 1270.f, 504.f };

	/*sf::Vector2f point1 = { 855.f, 280.f};
	sf::Vector2f point2 = { 584.f, 434.f};
	sf::Vector2f point3 = { 764.f, 537.f };
	sf::Vector2f point4 = { 1034.f, 381.f };
	sf::Vector2f point5 = { 1270.f, 516.f };*/

	sf::Vector2f direction = { 0,0 };


	float speed = 0.f;
	int maxHp = 0;
	int hp = 0;
	float enemyAccel = 0.f; // ���ӵ�

	bool flipX = false; // 90���� ȸ���ؾߵɰŰ�����
	bool beatWall = false; // �� �浹

	Tower* tower = nullptr;
	SoundGo* hitedSound = nullptr;

	// ������ ���Ҹ� ���� ���
	bool realEndPoint = false;

public:
	// ObjectPool<Tower> towerPool;

	Enemy(const std::string& textureId = "", const std::string n = "");
	virtual~Enemy()override;

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	void SetType(Types t);
	Types GetType() const;

	// ���Ͱ� Ÿ������ �´ºκ�
	void SetTowerList(const std::list<Tower*>* list);
	void OnTakeDamege(int damage);  // �ʼ�

	// ���� ��? void SetWall(); 
	void SetSound(SoundGo* hitSound) { hitedSound = hitSound; }

	// ������ ���Ҹ� ���� �Լ�
	bool HasrealEndPoint() const;
	void SetrealEndPoint(bool arrived); // ��������

};

