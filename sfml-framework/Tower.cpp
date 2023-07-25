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
	arrowSpeed = info.arrowSpeed;
	attackRate = info.attackRate;
	//price = info.price;                     // Ÿ������ �˻���
	sortLayer = 6;
	//SetActive(false);
}

void Tower::Update(float dt)
{
	//animation.Update(dt);          // �ַο� �ȿ��� �ִϹ� �ް�    
	SpriteGo::Update(dt);       // Ÿ�� -> ȭ�� -> �ִϹ�


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
			enemy = nullptr; // Ÿ���� ��Ÿ��� ���Ͱ� ����ٴ� �Ŵϱ� ��ptr��
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

	// �� ���̴� ����Ʈ�� �ѹ���
	// �� �Լ� �ȿ��� �� ���� �� �ʱ�ȭ
	// ����� ������

	for (auto enemy : *enemys)
	{
		float distance = Utils::Distance({ this->position.x, this->position.y}, { enemy->GetPosition().x, enemy->GetPosition().y + 42 });
		//std::cout << "Distance: " << distance << std::endl;
		sf::Vector2f Realposition = { enemy->GetPosition().x, enemy->GetPosition().y + 32 };

		direction = Utils::Normalize(Realposition - position);
		// ���� ������ - Ÿ��������

		if (distance <= range)
		{
			//std::cout << "��" << std::endl;

			Arrow* arrow = poolArrows->Get();
			arrow->SetPosition(this->position);
			arrow->SetType(Arrow::Types::Arrow); //(Arrow::Types::Arrow); // �ϴ� ȭ�츸
			arrow->Aiming({GetPosition().x, GetPosition().y - 42}, direction, arrowSpeed, range, damage);
			//info.arrowSpeed�� �۵��� ����
			sceneDev1->AddGo(arrow);
			return;

			//enemy->GetPosition();
			// tower->GetEnemy(this); // ���Ͱ� Ÿ�����ٰ� �ڱ� ������ �ѱ�°�
			//tower->Getdistanc(this)
			 // �ѹ���
			// Ÿ���� �� �ڽ��� ��ġ
			// �̷��� �ҰŸ� ������ ���⼭ �Ѱ��־����
		}
		
	}


	//arrow->Aiming(speed, range, damage, direction);


	//if (sceneDev1 != nullptr)
	//{
	//	arrow->SetEnemyList(sceneDev1->GetEnemyList());
	//	sceneDev1->AddGo(arrow); // �����͸� �ѱ�� �����꿡�� ó��
	//}
	
}