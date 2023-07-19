#include "stdafx.h"
#include "Tower.h"
#include "TowerTable.h"

#include "InputMgr.h"
#include "TileMap.h" // 7-17 ���ºκ� ���� �߰�


void Tower::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
}


void Tower::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	//����
}


void Tower::Init()
{

	animation.SetTarget(&sprite);
	SetOrigin(Origins::BC);
}

void Tower::Reset()
{
	SpriteGo::Reset();

	//animation.Play("Bow_Idle");
	SetOrigin(origin);
	//SetPosition({ 100, 200 }); // �� �������� Ÿ�� Ŭ�� ���Ÿ��
	sortLayer = 6;
	//SetActive(false);
}

void Tower::Update(float dt)
{
	animation.Update(dt);
	SpriteGo::Update(dt);


	// �ַο� �ȿ��� �ִϹ� �ް�
	// Ÿ�� -> ȭ�� -> �ִϹ�

	position += direction * speed * dt;
	sprite.setPosition(position);

	

}

void Tower::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

sf::Vector2f Tower::GetSize()
{
	sf::Vector2f size = { 50, 64 };


	//size.x = sprite.getGlobalBounds().width;
	//size.y = sprite.getGlobalBounds().height;

	return size;

	// return sf::Vector2f();
}

sf::Vector2f Tower::GetCenter()
{
	sf::Vector2f size = { 50, 64 };
	sf::Vector2f center;

	center.x = size.x + size.y / 2;
	center.y = size.x + size.y / 2;

	return center;

	// return sf::Vector2f();
}

bool Tower::Load(const std::string& filePath)
{
	//SetPosition(0, 100);

	return true;
}

void Tower::SetType(Types t)
{
	towerType = t;

	const TowerInfo& info = DATATABLE_MGR.Get<TowerTable>(DataTable::Ids::Tower)->Get(t); // ���� �̶��� �𸣴ϱ� ���� ��������

	int index = (int)towerType;
	textureId = info.textureId; // �ʱ�ȭ �� �� �ֲ�?
}

Tower::Types Tower::GetType() const
{
	return towerType;
}





//void Tower::TowerAttack(const sf::Vector2f& position, const sf::Vector2f& look, float dt)
//{
//
//
//
//}





// ����
//void Tower::rotateDiamond(sf::ConvexShape& diamond, float angle)
//{
//
//	sf::Vector2f center(diamondWidth / 2.f, diamondHeight / 2.f);
//	diamond.setOrigin(center);
//	diamond.setRotation(angle);
//	
//}
