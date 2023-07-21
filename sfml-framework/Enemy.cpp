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

#include "DataTableMgr.h" // 18�� ���ῡ ������ �߰�

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
	// ���� 1���� �� �ҰŸ� Types::Ufo1 �̷��� �ص� �ȴ�
	// 18�� ���� �߰�
	// ���̺��� ��°�ΰ����´�

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

	direction = Utils::Normalize(currPoint - position); // ���� ���ϰ�

	position += direction * speed * dt;
	sprite.setPosition(position); // �߰�


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
				sceneDev1->EnemyEndPoint(this); // �����͸� �ѱ�� �����꿡�� ó��
			}

		}

}



void Enemy::SetType(Types t)
{
	enemyType = t;

	const EnemyInfo& info = DATATABLE_MGR.Get<EnemyTable>(DataTable::Ids::Enemy)->Get(t);

	int index = (int)enemyType;
	textureId = info.textureId; // �ʱ�ȭ �� �� �ֲ�?
	/*textureId = info.speed;
	textureId = info.maxHp;*/

}

Enemy::Types Enemy::GetType() const
{
	return enemyType;
}


void Enemy::SetPlayer(Tower* tower)
{
	this->tower = tower; // Ÿ���� ��ġ���� �ޱ�����
}

void Enemy::OnTakeDamege(int damage)
{
	hp -= damage; // hitedSound->sound.play(); ����� ���߿�

	if (hp <= 0)
	{
		Scene* scene = SCENE_MGR.GetCurrScene(); //����ȯ������ ����
		SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
		if (sceneDev1 != nullptr)
		{
			sceneDev1->OnDieEnemy(this);
			// RemoveGo(enemy);
			// zombiePool.Return(zombie);
			// ������ �ؾ��ϴϱ� �����꿡 �״�ó�� �Լ� �����
		}
	}
}

void Enemy::GetSearchTower()
{

	// ���� �� > Ÿ�� 6��
	// �����κ��� Ÿ���� �ѱ��
	// ���ݵ� �ַο� ������Ʈ�� �ƴ϶�
	// ���ݵ� Ÿ������ �ϰ�
	
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
			std::cout << "��" << std::endl;
			tower->GetEnemy(this); // ���Ͱ� Ÿ�����ٰ� �ڱ� ������ �ѱ�°�
			//tower->Getdistanc(this)
			return; // �ѹ���
			// Ÿ���� �� �ڽ��� ��ġ
			// �̷��� �ҰŸ� ������ ���⼭ �Ѱ��־����
		}
	}

}




// ����
bool Enemy::GetFlipX() const
{
	return flipX;
}

void Enemy::SetFlipX(bool flip)
{
	flipX = flip;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !flipX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale); // �ǽ���������
}

void Enemy::SetTowerList(const std::list<Tower*>* list)
{
	towers = list;
}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}