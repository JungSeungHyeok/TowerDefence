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
	SpriteGo::Reset();
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

	speed = 130.f;

	float distance = Utils::Distance(currPoint, position);

	direction = Utils::Normalize(currPoint - position); // 방향 구하고
	sprite.setRotation(Utils::Angle(direction)); // 추가 // 이미지가 움직인다

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
	hitedSound->sound.play(); // 맞은 다음에

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