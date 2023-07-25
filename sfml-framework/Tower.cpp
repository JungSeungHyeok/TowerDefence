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
	arrowSpeed = info.arrowSpeed;
	attackRate = info.attackRate;
	//price = info.price;                     // 타워정보 검색용
	sortLayer = 6;
	//SetActive(false);
}

void Tower::Update(float dt)
{
	//animation.Update(dt);          // 애로우 안에서 애니미 받고    
	SpriteGo::Update(dt);       // 타워 -> 화살 -> 애니미


	//if (enemy != nullptr)
	attackTrigger += dt;
	
	if (attackTrigger >= attackRate)
	{
		TowerAttack();
		attackTrigger = 0.f;
	}

	//std::cout << "attackTrigger: " << attackTrigger << std::endl;
	// arrowTowerAttack()
	// wizadTowerAttack()


	//GetSearchEnemy();
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
	damage = info.damage;
	range = info.range;
	arrowSpeed = info.arrowSpeed;
	attackRate = info.attackRate;
	//price = info.price;
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

void Tower::SetArrowList(const std::list<Arrow*>* list)
{
	arrows = list;
}

void Tower::GetEnemy(Enemy* enemy)
{
	/*if (this->enemy == nullptr)
		this->enemy = enemy;*/
}

void Tower::TowerAttack()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);

	// 셋 에미니 리스트는 한번만
	// 그 함수 안에는 뭐 인포 다 초기화
	// 에드고 마지막

	for (auto enemy : *enemys)
	{
		float distance = Utils::Distance({ this->position.x, this->position.y}, { enemy->GetPosition().x, enemy->GetPosition().y + 42 });
		//std::cout << "Distance: " << distance << std::endl;
		sf::Vector2f Realposition = { enemy->GetPosition().x, enemy->GetPosition().y + 32 };

		direction = Utils::Normalize(Realposition - position);
		// 몬스터 포지션 - 타워포지션

		if (distance <= range)
		{
			//std::cout << "쏨" << std::endl;

			Arrow* arrow = poolArrows->Get();
			arrow->SetPosition(this->position);
			arrow->SetType(Arrow::Types::Arrow); //(Arrow::Types::Arrow); // 일단 화살만
			arrow->Aiming({GetPosition().x, GetPosition().y - 42}, direction, arrowSpeed, range, damage);
			//info.arrowSpeed가 작동을 안함
			sceneDev1->AddGo(arrow);
			return;

			//enemy->GetPosition();
			// tower->GetEnemy(this); // 몬스터가 타워에다가 자기 본인을 넘기는것
			//tower->Getdistanc(this)
			 // 한번만
			// 타워와 나 자신의 위치
			// 이렇게 할거면 방향을 여기서 넘겨주어야함
		}
		
	}


	//arrow->Aiming(speed, range, damage, direction);


	//if (sceneDev1 != nullptr)
	//{
	//	arrow->SetEnemyList(sceneDev1->GetEnemyList());
	//	sceneDev1->AddGo(arrow); // 데이터만 넘기고 씬데브에서 처리
	//}
	
}