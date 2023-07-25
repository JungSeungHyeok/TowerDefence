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
		for (auto enemy : *enemys) // -1�������� ����
			// 10���� �����ϸ� 9������ �������
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
	textureId = info.textureId; // �ʱ�ȭ �� �� �ֲ�?

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
	this->position = pos; // Ÿ���� ������
	this->direction = direction; // ������ ����

	this->damage = damage;
	this->range = range;
	this->speed = speed; // ������ ������ �ȵ�

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
//	// �̰� ���� ����� �Ÿ���
//
//	sf::Vector2f towerPosition = GetPosition();
//
//	for (const auto& enemy : *enemys)
//	{
//		float distance = Utils::Distance(GetPosition(), enemy->GetPosition()); // �Ÿ�
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
