#include "stdafx.h"
#include "Arrow.h"
#include "ArrowTable.h"

void Arrow::SetEnemyList(const std::list<Enemy*>* list)
{
	enemys = list;
}

void Arrow::Aiming(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed)
{	// 타워에서 제일 가까운 몬스터 겟포지션
	// 룩으로 애니메이션 쳐다보게하고
	// 맞으면 데미지주고

	// sprite.setRotation(Utils::Angle(dir)); 이건 잘모름

	SetPosition(pos);
	direction = dir;
	this->speed = speed;

	//SetActive(true);
}

void Arrow::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Arrow::Reset()
{
	SpriteGo::Reset();
	SetOrigin(origin);
	sortLayer = 7;
}

void Arrow::Update(float dt)
{

	SpriteGo::Update(dt);
	// 타워에서 제일 가까운 몬스터 겟포지션
	// 룩으로 애니메이션 쳐다보게하고
	// 맞으면 데미지주고



}

void Arrow::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

bool Arrow::Load(const std::string& filePath)
{
	return true;
}

void Arrow::SetType(Types t)
{
	arrowType = t;

	const ArrowInfo& info = DATATABLE_MGR.Get<ArrowTable>(DataTable::Ids::Arrow)->Get(t);

	int index = (int)arrowType;
	textureId = info.textureId; // 초기화 할 수 있께?
}

Arrow::Types Arrow::GetType() const
{
	return arrowType;
}

//Enemy* Arrow::MostCloseEnemy()
//{
//	Enemy* mostCloseEnemy = nullptr;
//
//	float minDistance = std::numeric_limits<float>::max();
//	// 이게 가장 가까운 거리고
//
//	sf::Vector2f towerPosition = GetPosition();
//
//	for (const auto& enemy : *enemys)
//	{
//		float distance = Utils::Distance(GetPosition(), enemy->GetPosition()); // 거리
//
//		if (distance >= range)
//		{
//			//SetActive(false);
//			//return;
//		}
//	}
//
//	return mostCloseEnemy;
//}
