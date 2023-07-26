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
	
	


	hpBackground.setSize(sf::Vector2f(hpBarWidth, hpBarHeight));
	hpBackground.setFillColor(sf::Color::White);
	hpBackground.setPosition(position.x - hpBarWidth / 2, position.y - 20.f);

	hpBar.setSize(sf::Vector2f(hpBarWidth, hpBarHeight));
	hpBar.setFillColor(sf::Color::Green);
	hpBar.setPosition(position.x - hpBarWidth / 2, position.y - 20.f);
	sortLayer = 7;
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

	//std::cout << position.x << ", " << position.y << std::endl;
	float distance = Utils::Distance(currPoint, position);

	direction = Utils::Normalize(currPoint - position); // 방향 구하고

	float enemyHpPercent = static_cast<float>(hp) / static_cast<float>(maxHp);
	float hpBarWidth = enemyHpPercent * 40.f;
	hpBar.setSize(sf::Vector2f(hpBarWidth, hpBarHeight));


	position += direction * speed * dt;
	sprite.setPosition(position); // 추가

	hpBar.setPosition(position);

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
	speed = info.speed;
	hp = info.maxHp;
	
	// 크기가 다 똑같으면 상관없는데 크기가 다르면 짤려서 나오니까
	// 스
	sprite.setTexture(*RESOURCE_MGR.GetTexture(textureId)); // 이렇게 텍스쳐를 새로지정하는것도 추가를 해주어야함
	//SetOrigin(Origins::MC);

	

}

Enemy::Types Enemy::GetType() const
{
	return enemyType;
}


void Enemy::SetTowerList(const std::list<Tower*>* list)
{
	towers = list;
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
bool Enemy::HasrealEndPoint() const
{
	return realEndPoint;
}
void Enemy::SetrealEndPoint(bool arrived)
{
	realEndPoint = arrived;
}
void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}