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
	//RESOURCE_MGR.Load(ResourceTypes::Texture, "Towers/Archer/archer_level_1.png");

	/*RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Bow_Idle.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Bow_Arrow.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Archer_Tower.csv");

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Bow_Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Bow_Arrow.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Archer_Tower.csv"));*/

	// attackTimer = attackRate;

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

//void Tower::InstallTower(const sf::Vector2f& isoTileCoords, const sf::Vector2f& tileSize)
//{
//
//	if (!isInstalled)
//	{
//		sf::Vector2f tileCenter(isoTileCoords.x * tileSize.x + tileSize.x / 2.0f, isoTileCoords.y * tileSize.y + tileSize.y / 2.0f);
//		SetPosition(tileCenter);
//		isInstalled = true;
//		// Ÿ�� �߽� ��ġ �߰�
//
//
//		//SetPosition(isoTileCoords.x * tileSize.x, isoTileCoords.y * tileSize.y);
//		//isInstalled = true;
//	}
//}

void Tower::SetType(Types t)
{
	towerType = t;

	const TowerInfo& info = DATATABLE_MGR.Get<TowerTable>(DataTable::Ids::Tower)->Get(t);

	int index = (int)towerType;
	textureId = info.textureId; // �ʱ�ȭ �� �� �ֲ�?
}

Tower::Types Tower::GetType() const
{
	return towerType;
}

void Tower::TowerAttack(int damage)
{
	
	//if (// ���� ���� ���� �Ұ� ���ǽ� ������ ����)
	//{
	//	return;
	//}
	// hp = std::max(hp - damdge, 0);


}



// ����
//void Tower::rotateDiamond(sf::ConvexShape& diamond, float angle)
//{
//
//	sf::Vector2f center(diamondWidth / 2.f, diamondHeight / 2.f);
//	diamond.setOrigin(center);
//	diamond.setRotation(angle);
//	
//}
