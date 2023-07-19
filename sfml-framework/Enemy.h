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


	// 포인트 1,23,4,5는 고정값 꺽이는 값을 처음에 넣어두고
	// 포인트 1에 도착했으면 커렌트 포인트에 2를 넣어준다
	//

	sf::Vector2f currPoint;


	sf::Vector2f point1 = { 855.f, 280.f};
	sf::Vector2f point2 = { 584.f, 434.f};
	sf::Vector2f point3 = { 764.f, 537.f };
	sf::Vector2f point4 = { 1034.f, 381.f };
	sf::Vector2f point5 = { 1270.f, 516.f };

	sf::Vector2f direction;

	float speed = 0.f;
	int maxHp = 0;
	int hp = 0;
	float enemyAccel = 0.f; // 가속도

	bool flipX = false; // 90도로 회전해야될거같은데

	bool beatWall = false; // 벽 충돌
	//{
		//월드포지션
	//몬스터가 이동할 위치를 계산을 해보면 
	// 벽에 해당하는 타일들 눈으로 구별 가능하니까
	// 만들어지는 자리에다가 충돌처리에 사용될
	//바인드라던가 쉐이프라던가 만들어놓고
	// 경계에 해당하는 자리에다가 

	//}


	Tower* tower = nullptr;
	SoundGo* hitedSound = nullptr;

	// std::list<Enemy> enemys;

public:
	Enemy(const std::string& textureId = "", const std::string n = "");
	virtual~Enemy()override;

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;

	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	void OnHit(int damage);

	void SetType(Types t);
	Types GetType() const;


	// 정면 벽? void SetWall(); 
	void SetSound(SoundGo* hitSound) { hitedSound = hitSound; }


	// 몬스터가 타워한테 맞는부분
	void SetPlayer(Tower* tower);
	void OnTakeDamege(int damage);


	bool GetFlipX() const;
	void SetFlipX(bool flip);

};

