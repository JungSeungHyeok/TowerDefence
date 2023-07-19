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

	LostEnemy(); // ���� �Ҿ���ȴ���? ��Ÿ� �ۿ� ������




	//sf::Vector2f look;
	//float speed = 100.f;

	//sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	//sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrScene()->ScreenToWorldPos(mousePos);
	//sf::Vector2f playerScreenPos = SCENE_MGR.GetCurrScene()->WorldPosToScreen(position);

	//// ȸ��
	//look = Utils::Normalize(mousePos - playerScreenPos);
	//sprite.setRotation(Utils::Angle(look));

	//// �̵�
	//direction.x = INPUT_MGR.GetAxis(Axis::Horizontal);
	//direction.y = INPUT_MGR.GetAxis(Axis::Vertical);
	//float magnitude = Utils::Magnitude(direction);
	//if (magnitude > 1.f)
	//{
	//	direction /= magnitude;
	//}


	//std::cout << direction.x << std::endl;

	//position += direction * speed * dt;
	//sprite.setPosition(position);

	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::A))
	//{
	//	Arrow* arrow = poolArrows.Get();
	//	arrow->Aiming(GetPosition(), look, 1000.f);

	//	Scene* scene = SCENE_MGR.GetCurrScene();
	//	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);
	//	if (sceneDev1 != nullptr)
	//	{
	//		arrow->SetEnemyList(sceneDev1->GetEnemyList());
	//		sceneDev1->AddGo(arrow);
	//	}
	//}








	//sf::Vector2f posTest1 = {400, 450};
	//sf::Vector2f posTest2 = { 450, 450 };

	//float distance = Utils::Distance(posTest1, posTest2);

	//direction = Utils::Normalize(posTest1 - posTest2); // ���� ���ϰ�

	//position += direction * arrowSpeed * dt;
	//sprite.setPosition(position); // �߰�

	

	


}

void Tower::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

sf::Vector2f Tower::GetSize()
{
	sf::Vector2f size = { 50, 64 };
	return size;
}

sf::Vector2f Tower::GetCenter()
{
	sf::Vector2f size = { 50, 64 };
	sf::Vector2f center;

	center.x = size.x + size.y / 2;
	center.y = size.x + size.y / 2;

	return center;
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
			enemy = nullptr; // Ÿ���� ��Ÿ��� ���Ͱ� ����ٴ� �Ŵϱ� ��ptr��
		}
	}
}

void Tower::SetEnemyList(const std::list<Enemy*>* list)
{
	enemys = list;
}




void Tower::TowerAttack()
{
	
	auto info = DATATABLE_MGR.Get<ArrowTable>(DataTable::Ids::Arrow)->Get(Arrow::Types::Arrow);

	arrow = poolArrows->Get();
	arrow->SetType(info.arrowType);           //(Arrow::Types::Arrow); // �ϴ� ȭ�츸
	arrow->SetArrowSpeed(info.speed);
	arrow->SetRange(info.range);
	arrow->SetDamage(info.damage);




	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneDev1* sceneDev1 = dynamic_cast<SceneDev1*>(scene);

	if (sceneDev1 != nullptr)
	{
		sceneDev1->AddGo(arrow); // �����͸� �ѱ�� �����꿡�� ó��
	}

}





//void Tower::SetEnemyList(const std::list<Enemy*>* list)
//{
//	enemys = list;
//}



// ����
//void Tower::rotateDiamond(sf::ConvexShape& diamond, float angle)
//{
//
//	sf::Vector2f center(diamondWidth / 2.f, diamondHeight / 2.f);
//	diamond.setOrigin(center);
//	diamond.setRotation(angle);
//	
//}
