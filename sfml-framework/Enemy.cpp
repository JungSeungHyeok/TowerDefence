#include "stdafx.h"

#include "Enemy.h"
#include "EnemyTable.h"

#include "Tower.h"

#include "ResourceMgr.h"
#include "SoundGo.h"
#include "DataTableMgr.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "SceneDev1.h"

#include "DataTableMgr.h" // 18일 저녁에 집에서 추가

Enemy::Enemy(const std::string& textureId, const std::string n)
	:SpriteGo(textureId, n)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
	

	currPoint = point1;
}

void Enemy::Reset()
{
	// 리셋 1라운드 몹 할거면 Types::Ufo1 이렇게 해도 된다
	// 18일 저녁 추가
	// 테이블을 통째로가져온다

	SpriteGo::Reset();

	auto info = DATATABLE_MGR.Get<EnemyTable>(DataTable::Ids::Enemy)->Get(enemyType);

	speed = info.speed;
	maxHp = info.maxHp;
	hp = maxHp;
	currPoint = point1;
	sortLayer = 4;
}

void Enemy::Release()
{
	SpriteGo::Release();
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

	GetSearchTower();

	//std::cout << position.x << ", " << position.y << std::endl;
	float distance = Utils::Distance(currPoint, position);

	direction = Utils::Normalize(currPoint - position); // 방향 구하고

	position += direction * speed * dt;
	sprite.setPosition(position); // 추가


	if (currPoint == point1)
		if (Utils::Distance(point1, position) < 0.5f)
			currPoint = point2;
	
	if (currPoint == point2)
		if (Utils::Distance(point2, position) < 0.5f)
			currPoint = point3;

	if (currPoint == point3)
		if (Utils::Distance(point3, position) < 0.5f)
			currPoint = point4;

	if (currPoint == point4)
		if (Utils::Distance(point4, position) < 0.5f)
			currPoint = point5;

	if (currPoint == point5)
		if (Utils::Distance(point5, position) < 0.5f)
		{
			Scene* scene = SCENE_MGR.GetCurrScene();
			SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);

			if (sceneDev1 != nullptr)
			{
				sceneDev1->EnemyEndPoint(this); // 데이터만 넘기고 씬데브에서 처리
			}

		}

}



void Enemy::SetType(Types t)
{
	enemyType = t;

	const EnemyInfo& info = DATATABLE_MGR.Get<EnemyTable>(DataTable::Ids::Enemy)->Get(t);

	int index = (int)enemyType;
	textureId = info.textureId; // 초기화 할 수 있께?
	/*textureId = info.speed;
	textureId = info.maxHp;*/

}

Enemy::Types Enemy::GetType() const
{
	return enemyType;
}


void Enemy::SetPlayer(Tower* tower)
{
	this->tower = tower; // 타워의 위치값을 받기위해
}

void Enemy::OnTakeDamege(int damage)
{
	hp -= damage; // hitedSound->sound.play(); 사운드는 나중에

	if (hp <= 0)
	{
		Scene* scene = SCENE_MGR.GetCurrScene(); //형변환연산자 쓰기
		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
		if (sceneDev1 != nullptr)
		{
			sceneDev1->OnDieEnemy(this);
			// RemoveGo(enemy);
			// zombiePool.Return(zombie);
			// 리무브 해야하니까 씬데브에 죽는처리 함수 만들기
		}
	}
}

void Enemy::GetSearchTower()
{

	// 몬스터 수 > 타워 6개
	// 감지부분은 타워에 넘기고
	// 공격도 애로우 업데이트가 아니라
	// 공격도 타워에서 하고
	
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
	if (sceneDev1 != nullptr)
	{
		SetTowerList(sceneDev1->GetTowerList());
	}
	for (auto tower : *towers)
	{
		float distance = Utils::Distance(this->position, tower->GetPosition());
		std::cout << "Distance: " << distance << std::endl;

		/*if (tower->CheckEnemy())
			return;*/

		if (distance <= tower->GetRange())
		{
			std::cout << "쏨" << std::endl;
			tower->GetEnemy(this); // 몬스터가 타워에다가 자기 본인을 넘기는것
			//tower->Getdistanc(this)
			return; // 한번만
			// 타워와 나 자신의 위치
			// 이렇게 할거면 방향을 여기서 넘겨주어야함
		}
	}

}




// 보류
bool Enemy::GetFlipX() const
{
	return flipX;
}

void Enemy::SetFlipX(bool flip)
{
	flipX = flip;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale); // 실습과제참고
}

void Enemy::SetTowerList(const std::list<Tower*>* list)
{
	towers = list;
}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}