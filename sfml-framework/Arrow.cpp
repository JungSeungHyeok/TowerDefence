#include "stdafx.h"
#include "Arrow.h"
#include "ArrowTable.h"

void Arrow::SetEnemyList(const std::list<Enemy*>* list)
{
	enemys = list;
}

void Arrow::Aiming(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed)
{	// Ÿ������ ���� ����� ���� ��������
	// ������ �ִϸ��̼� �Ĵٺ����ϰ�
	// ������ �������ְ�

	// sprite.setRotation(Utils::Angle(dir)); �̰� �߸�

	SetPosition(pos);
	direction = dir;
	this->speed = speed;

	//SetActive(true);
}

void Arrow::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Arrow::Reset()
{
	SpriteGo::Reset();
	SetOrigin(origin);
	sortLayer = 7;
}

void Arrow::Update(float dt)
{

	SpriteGo::Update(dt);
	// Ÿ������ ���� ����� ���� ��������
	// ������ �ִϸ��̼� �Ĵٺ����ϰ�
	// ������ �������ְ�



}

void Arrow::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

bool Arrow::Load(const std::string& filePath)
{
	return true;
}

void Arrow::SetType(Types t)
{
	arrowType = t;

	const ArrowInfo& info = DATATABLE_MGR.Get<ArrowTable>(DataTable::Ids::Arrow)->Get(t);

	int index = (int)arrowType;
	textureId = info.textureId; // �ʱ�ȭ �� �� �ֲ�?
}

Arrow::Types Arrow::GetType() const
{
	return arrowType;
}

//Enemy* Arrow::MostCloseEnemy()
//{
//	Enemy* mostCloseEnemy = nullptr;
//
//	float minDistance = std::numeric_limits<float>::max();
//	// �̰� ���� ����� �Ÿ���
//
//	sf::Vector2f towerPosition = GetPosition();
//
//	for (const auto& enemy : *enemys)
//	{
//		float distance = Utils::Distance(GetPosition(), enemy->GetPosition()); // �Ÿ�
//
//		if (distance >= range)
//		{
//			//SetActive(false);
//			//return;
//		}
//	}
//
//	return mostCloseEnemy;
//}
