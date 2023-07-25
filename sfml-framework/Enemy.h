#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "AnimationController.h"

// 몬스터 충돌 체크할때 이미지 띄워서 하기?

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
	float enemyAccel = 0.f; // 가속도

	bool flipX = false; // 90도로 회전해야될거같은데
	bool beatWall = false; // 벽 충돌

	Tower* tower = nullptr;
	SoundGo* hitedSound = nullptr;

	// 라이프 감소를 위한 멤버
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

	// 몬스터가 타워한테 맞는부분
	void SetTowerList(const std::list<Tower*>* list);
	void OnTakeDamege(int damage);  // 필수

	// 정면 벽? void SetWall(); 
	void SetSound(SoundGo* hitSound) { hitedSound = hitSound; }

	// 라이프 감소를 위한 함수
	bool HasrealEndPoint() const;
	void SetrealEndPoint(bool arrived); // 도착여부

};

