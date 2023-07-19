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
}

void Enemy::Release()
{
	SpriteGo::Release();
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

	//speed = 130.f;






	float distance = Utils::Distance(currPoint, position);

	// 실시간 몬스터 위치 + 타워위치


	direction = Utils::Normalize(currPoint - position); // 방향 구하고

	//sprite.setRotation(Utils::Angle(direction)); // 추가 // 이미지가 움직인다

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





	//// 거리가 1보다 작으면은
	//if (Utils::Distance(point1,position) < 0.5f) // 가상의 점과 몬스터 포지션 겹치면 currPoint +1+2+3+4 바꾸기
	//{
	//	currPoint = point2; // 546, 429 넣고
	//}












	/*sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	speed = 0.001f;

	

	position += direction * speed * dt;

	SetPosition(mousePos);*/

//	SetPosition(uiMousePos);



	/*float distance = Utils::Distance(tower->GetPosition(), position);

	look = direction = Utils::Normalize(tower->GetPosition() - position);
	sprite.setRotation(Utils::Angle(look));*/

	/*if (tower == nullptr)
	{
		return;
	}*/

	// 몬스터는 생성시에 스타트 포인트의 정면방향
	// 부딪히고나면 이동하는 방향, 룩도 90도 회전

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

//void Enemy::SetWall()
//{
//}

void Enemy::OnHit(int damage)
{
	hp -= damage;
	//hitedSound->sound.play(); // 맞은 다음에

	if (hp <= 0)
	{
		Scene* scene = SCENE_MGR.GetCurrScene();
		
		//형변환연산자 쓰기
		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
		if (sceneDev1 != nullptr)
		{
			sceneDev1->OnDieEnemy(this);
		}
	}
}


void Enemy::SetPlayer(Tower* tower)
{
	this->tower = tower; // 타워의 위치값을 받기위해
}

void Enemy::OnTakeDamege(int damage)
{
	// 이렇게 해봤자 csv값은 아니잖아
	// (towerType& tower) 이런 느낌으로 인자를 받아온게 아니라
	// 근데 좀비테이블도 이 형식이긴해 / 뭐 다른거 없고
	

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

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

