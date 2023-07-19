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


	// ����Ʈ 1,23,4,5�� ������ ���̴� ���� ó���� �־�ΰ�
	// ����Ʈ 1�� ���������� Ŀ��Ʈ ����Ʈ�� 2�� �־��ش�
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
	float enemyAccel = 0.f; // ���ӵ�

	bool flipX = false; // 90���� ȸ���ؾߵɰŰ�����

	bool beatWall = false; // �� �浹
	//{
		//����������
	//���Ͱ� �̵��� ��ġ�� ����� �غ��� 
	// ���� �ش��ϴ� Ÿ�ϵ� ������ ���� �����ϴϱ�
	// ��������� �ڸ����ٰ� �浹ó���� ����
	//���ε����� ����������� ��������
	// ��迡 �ش��ϴ� �ڸ����ٰ� 

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


	// ���� ��? void SetWall(); 
	void SetSound(SoundGo* hitSound) { hitedSound = hitSound; }


	// ���Ͱ� Ÿ������ �´ºκ�
	void SetPlayer(Tower* tower);
	void OnTakeDamege(int damage);


	bool GetFlipX() const;
	void SetFlipX(bool flip);

};

