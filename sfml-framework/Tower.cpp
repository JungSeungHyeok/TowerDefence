#include "stdafx.h"
#include "Tower.h"
#include "TowerTable.h"

#include "InputMgr.h"
#include "TileMap.h" // 7-17 ���ºκ� ���� �߰�

#include "SceneDev1.h"
#include "ArrowTable.h"


void Tower::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
}


void Tower::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	//����
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
	price = info.price;                     // Ÿ������ �˻���
	sortLayer = 6;
	//SetActive(false);
}

void Tower::Update(float dt)
{
	//animation.Update(dt);          // �ַο� �ȿ��� �ִϹ� �ް�    
	SpriteGo::Update(dt);       // Ÿ�� -> ȭ�� -> �ִϹ�


	//if (enemy != nullptr)
	TowerAttack();





	GetSearchEnemy();
	//LostEnemy(); // ���� �Ҿ���ȴ���? ��Ÿ� �ۿ� ������
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
	textureId = info.textureId; // �ʱ�ȭ �� �� �ֲ�?
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
			enemy = nullptr; // Ÿ���� ��Ÿ��� ���Ͱ� ����ٴ� �Ŵϱ� ��ptr��
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
	// �ַο켼��
	auto info = DATATABLE_MGR.Get<ArrowTable>(DataTable::Ids::Arrow)->Get(Arrow::Types::Arrow);
	Arrow* arrow = poolArrows->Get();
	arrow->SetPosition(this->position);
	arrow->SetType(info.arrowType); //(Arrow::Types::Arrow); // �ϴ� ȭ�츸
	// arrow->Aiming(speed, range, damage, direction); // ���̾��ְ�

	// �ִϹ̼���
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
	if (sceneDev1 != nullptr)
	{
		SetEnemyList(sceneDev1->GetEnemyList());
		//sceneDev1->AddGo(arrow);
	}

	

	direction = Utils::Normalize(enemy->GetPosition() - position); // ���� ������ - Ÿ��������

	

	for (auto enemy : *enemys)
	{
		float distance = Utils::Distance(this->position, enemy->GetPosition());
		std::cout << "Distance: " << distance << std::endl;

		if (distance <= range)
		{
			std::cout << "��" << std::endl;
			arrow->Aiming(speed, range, damage, direction);

			//enemy->GetPosition();
			// tower->GetEnemy(this); // ���Ͱ� Ÿ�����ٰ� �ڱ� ������ �ѱ�°�
			//tower->Getdistanc(this)
			return; // �ѹ���
			// Ÿ���� �� �ڽ��� ��ġ
			// �̷��� �ҰŸ� ������ ���⼭ �Ѱ��־����
		}
	}

	//Scene* scene = SCENE_MGR.GetCurrScene();
	//SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);

	//if (sceneDev1 != nullptr)
	//{
	//	arrow->SetEnemyList(sceneDev1->GetEnemyList());
	//	sceneDev1->AddGo(arrow); // �����͸� �ѱ�� �����꿡�� ó��
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
