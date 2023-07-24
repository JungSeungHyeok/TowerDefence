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

	speed = info.speed;
	range = info.range;
	damage = info.damage;
	sortLayer = 7;
}

void Arrow::Update(float dt)
{
	SpriteGo::Update(dt);

	range -= speed * dt;
	if (range < 0.f)
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		pool->Return(this);
	}

	position += direction * speed * dt * 10.f;
	sprite.setPosition(position);
	//SetPosition(position);

	if (enemys != nullptr)
	{
		for (auto enemy : *enemys)
		{
			if (this->sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds()))
			{
				enemy->OnTakeDamege(damage);

				SCENE_MGR.GetCurrScene()->RemoveGo(this);
				pool->Return(this);
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
}

Arrow::Types Arrow::GetType() const
{
	return arrowType;
}

void Arrow::Aiming(float range, float speed, int damage, sf::Vector2f direction)
{
	this->range = range;
	this->speed = speed;
	this->damage = damage;
	this->direction = direction;
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
