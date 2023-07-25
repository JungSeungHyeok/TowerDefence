#include "stdafx.h"
#include "Arrow.h"
#include "ArrowTable.h"
#include "SceneDev1.h"
#include "Enemy.h"

void Arrow::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Arrow::Reset()
{
	SpriteGo::Reset();
	auto info = DATATABLE_MGR.Get<ArrowTable>(DataTable::Ids::Arrow)->Get(Types::Arrow);

	damage = info.damage;
	range = info.range;
	speed = info.speed;
	sortLayer = 7;
}

void Arrow::Update(float dt)
{
	SpriteGo::Update(dt);

	range -= speed * dt * 3.f;
	if (range < 0.f)
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		arrowPool->Return(this);
	}

	position += direction * speed * dt * 3.f;

	sprite.setPosition(position);

	/*Scene* scene = SCENE_MGR.GetCurrScene();
	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
	SetEnemyList(sceneDev1->GetEnemyList());*/

	if (enemys != nullptr)
	{
		for (auto enemy : *enemys) // -1마리수가 찍힘
			// 10마리 생성하면 9마리만 담겨있음
		{
			if (this->sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds()))
			{
				enemy->OnTakeDamege(damage);

				SCENE_MGR.GetCurrScene()->RemoveGo(this);
				arrowPool->Return(this);
				break;
			}
		}
	}

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

	damage = info.damage;
	range = info.range;
	speed = info.speed;

}

Arrow::Types Arrow::GetType() const
{
	return arrowType;
}

void Arrow::Aiming(sf::Vector2f pos, sf::Vector2f direction, float speed, float range, int damage)
{
	this->position = pos; // 타워의 포지션
	this->direction = direction; // 몬스터쪽 방향

	this->damage = damage;
	this->range = range;
	this->speed = speed; // 넣으면 적용이 안됨

	float angle = Utils::Angle(direction);
	sprite.setRotation(angle + 90.f);

}

void Arrow::SetEnemyList(const std::list<Enemy*>* list)
{
	enemys = list;
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
