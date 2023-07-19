#include "stdafx.h"
#include "Tower.h"
#include "TowerTable.h"

#include "InputMgr.h"
#include "TileMap.h" // 7-17 리셋부분 참고 추가


void Tower::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
}


void Tower::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	//보류
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
	//SetPosition({ 100, 200 }); // 셋 포지션을 타일 클릭 가운데타워
	sortLayer = 6;
	//SetActive(false);
}

void Tower::Update(float dt)
{
	animation.Update(dt);
	SpriteGo::Update(dt);


	// 애로우 안에서 애니미 받고
	// 타워 -> 화살 -> 애니미

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

	const TowerInfo& info = DATATABLE_MGR.Get<TowerTable>(DataTable::Ids::Tower)->Get(t); // 내가 이뜻을 모르니까 거의 복붙이지

	int index = (int)towerType;
	textureId = info.textureId; // 초기화 할 수 있께?
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





// 보류
//void Tower::rotateDiamond(sf::ConvexShape& diamond, float angle)
//{
//
//	sf::Vector2f center(diamondWidth / 2.f, diamondHeight / 2.f);
//	diamond.setOrigin(center);
//	diamond.setRotation(angle);
//	
//}
