#include "stdafx.h"
#include "Tower.h"
#include "TowerTable.h"

#include "InputMgr.h"
#include "TileMap.h" // 7-17 리셋부분 참고 추가

#include "SceneDev1.h"
#include "ArrowTable.h"


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
	auto info = DATATABLE_MGR.Get<TowerTable>(DataTable::Ids::Tower)->Get(towerType);
	//SetOrigin(origin);

	damage = info.damage;
	range = info.range;
	attackRate = info.attackRate;
	arrowSpeed = info.arrowSpeed;
	price = info.price;                     // 타워정보 검색용
	sortLayer = 6;
	//SetActive(false);
}

void Tower::Update(float dt)
{
	//animation.Update(dt);          // 애로우 안에서 애니미 받고    
	SpriteGo::Update(dt);       // 타워 -> 화살 -> 애니미


	//if (enemy != nullptr)
	TowerAttack();





	GetSearchEnemy();
	//LostEnemy(); // 몬스터 잃어버렸는지? 사거리 밖에 나가서
}

void Tower::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}


bool Tower::Load(const std::string& filePath)
{
	return true;
}

void Tower::SetType(Types t)
{
	towerType = t;

	const TowerInfo& info = DATATABLE_MGR.Get<TowerTable>(DataTable::Ids::Tower)->Get(t);

	int index = (int)towerType;
	textureId = info.textureId; // 초기화 할 수 있께?
}

Tower::Types Tower::GetType() const
{
	return towerType;
}



void Tower::LostEnemy()
{
	if (enemy != nullptr)
	{
		float distance = Utils::Distance(position, enemy->GetPosition());
		if (distance > range)
		{
			//arrow->GetSearchEnemy();
			enemy = nullptr; // 타워의 사거리를 몬스터가 벗어났다는 거니까 널ptr로
		}
	}
}

void Tower::SetEnemyList(const std::list<Enemy*>* list)
{
	enemys = list;
}

void Tower::GetSearchEnemy()
{

}

void Tower::GetEnemy(Enemy* enemy)
{
	if (this->enemy == nullptr)
		this->enemy = enemy;
}

void Tower::TowerAttack()
{
	// 애로우세팅
	auto info = DATATABLE_MGR.Get<ArrowTable>(DataTable::Ids::Arrow)->Get(Arrow::Types::Arrow);
	Arrow* arrow = poolArrows->Get();
	arrow->SetPosition(this->position);
	arrow->SetType(info.arrowType); //(Arrow::Types::Arrow); // 일단 화살만
	// arrow->Aiming(speed, range, damage, direction); // 파이어있고

	// 애니미세팅
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
	if (sceneDev1 != nullptr)
	{
		SetEnemyList(sceneDev1->GetEnemyList());
		//sceneDev1->AddGo(arrow);
	}

	

	direction = Utils::Normalize(enemy->GetPosition() - position); // 몬스터 포지션 - 타워포지션

	

	for (auto enemy : *enemys)
	{
		float distance = Utils::Distance(this->position, enemy->GetPosition());
		std::cout << "Distance: " << distance << std::endl;

		if (distance <= range)
		{
			std::cout << "쏨" << std::endl;
			arrow->Aiming(speed, range, damage, direction);

			//enemy->GetPosition();
			// tower->GetEnemy(this); // 몬스터가 타워에다가 자기 본인을 넘기는것
			//tower->Getdistanc(this)
			return; // 한번만
			// 타워와 나 자신의 위치
			// 이렇게 할거면 방향을 여기서 넘겨주어야함
		}
	}

	//Scene* scene = SCENE_MGR.GetCurrScene();
	//SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);

	//if (sceneDev1 != nullptr)
	//{
	//	arrow->SetEnemyList(sceneDev1->GetEnemyList());
	//	sceneDev1->AddGo(arrow); // 데이터만 넘기고 씬데브에서 처리
	//}
	
}

//
//sf::Vector2f Tower::GetSize()
//{
//	sf::Vector2f size = { 50, 64 };
//	return size;
//}
//
//sf::Vector2f Tower::GetCenter()
//{
//	sf::Vector2f size = { 50, 64 };
//	sf::Vector2f center;
//
//	center.x = size.x + size.y / 2;
//	center.y = size.x + size.y / 2;
//
//	return center;
//}
