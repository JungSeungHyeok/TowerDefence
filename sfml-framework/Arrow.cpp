#include "stdafx.h"
#include "Arrow.h"
#include "ArrowTable.h"
#include "SceneDev1.h"
#include "Enemy.h"

void Arrow::SetEnemyList(const std::list<Enemy*>* list)
{
	enemys = list;
}

//const std::list<Enemy*>* Arrow::GetEnemyList() const
//{
//	return &enemyPool.GetUseList();
//}

void Arrow::GetSearchEnemy()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
	if (sceneDev1 != nullptr)
<<<<<<< HEAD

=======
>>>>>>> 23bf381ba8f6646ab9af25ee2139d23805fc0cfc
	{
		SetEnemyList(sceneDev1->GetEnemyList()); // �ѹ��� ȣ��ǵ��� ¥�ߵż� ��ġ���� �ؾ��ҵ�
	}

<<<<<<< HEAD
	for (auto enemy : *enemys)
	{
		direction = Utils::Normalize(enemy->GetPosition() - this->GetPosition());
	}

	
	  // �߻�Ǵ½��� // (auto enemy : *enemys)

	 // �̰� ���ڰ� �ϳ��� ������ ���Ϸ��� ������ - ���������� �ؾ���


	

=======


	for (auto enemy : *enemys)
	{
		direction = Utils::Normalize(enemy->GetPosition() - this->GetPosition()); // �̰� ���ڰ� �ϳ��� ������ ���Ϸ��� ������ - ���������� �ؾ���
	}

>>>>>>> 23bf381ba8f6646ab9af25ee2139d23805fc0cfc

}



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
	GetSearchEnemy(); // �� ó�� �ѹ���


	attackTime += dt;
	//std::cout << "attackTime: " << attackTime << std::endl;

	position += direction * speed * dt * 10.f;
	
	if (attackTime >= targetTime)
	{
		sprite.setPosition(position);
		attackTime = 0.0f;
	}

	//attackTime += dt;
	
	GetSearchEnemy(); // ��Ÿ�� �߰��ؾ���


	attackTime += dt;
	//std::cout << "attackTime: " << attackTime << std::endl;

	position += direction * speed * dt * 10.f;
	
	if (attackTime >= targetTime)
	{
		sprite.setPosition(position);
		attackTime = 0.0f;
	}

	range -= speed * dt;

	if (range < 0.f)
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		pool->Return(this);
	}

	//float attackTime = 0.0f;
	//float targetTime = 0.1f;

<<<<<<< HEAD
	/*for (auto obj : *enemys)
	{
		if (this->sprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds()))
		{
			obj->OnTakeDamege(damage);

			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			pool->Return(this);
		}
	}*/
	

	//

=======
	

	

>>>>>>> 23bf381ba8f6646ab9af25ee2139d23805fc0cfc
	//if (enemys != nullptr)
	//{
	//	for (auto obj : *enemys)
	//	{
	//		if (this->sprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds()))
	//		{
	//			obj->OnTakeDamege(damage);

	//			SCENE_MGR.GetCurrScene()->RemoveGo(this);
	//			pool->Return(this);
	//		}
	//	}
	//}

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
}

Arrow::Types Arrow::GetType() const
{
	return arrowType;
}

void Arrow::SetRange(float range)
{
	this->range = range;
}

void Arrow::SetArrowSpeed(float speed)
{
	this->speed = speed;
}

void Arrow::SetDamage(int damage)
{
	this->damage = damage;
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
