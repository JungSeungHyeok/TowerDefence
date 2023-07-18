#include "stdafx.h"
#include "Arrow.h"

Arrow::Arrow(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
}

Arrow::~Arrow()
{
}

void Arrow::SetEnemyList(const std::list<Enemy*>* list)
{
	enemys = list;
}

void Arrow::Aiming(const sf::Vector2f& pos, const sf::Vector2f& dir, float speed)
{	// 타워에서 제일 가까운 몬스터 겟포지션
	// 룩으로 애니메이션 쳐다보게하고
	// 맞으면 데미지주고

	// sprite.setRotation(Utils::Angle(dir)); 이건 잘모름

	SetPosition(pos);
	direction = dir;
	this->speed = speed;


}

void Arrow::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void Arrow::Release()
{
	SpriteGo::Release();
}

void Arrow::Reset()
{
	SpriteGo::Reset();
}

void Arrow::Update(float dt)
{
	SpriteGo::Update(dt);
	// 타워에서 제일 가까운 몬스터 겟포지션
	// 룩으로 애니메이션 쳐다보게하고
	// 맞으면 데미지주고

	
	for (const auto& enemy : *enemys) //리스트
	{
		float distance = Utils::Distance(GetPosition(), enemy->GetPosition());


		if (distance >= range)
		{


		}






	}

	//float distance = Utils::Distance(currPoint, position);

	//direction = Utils::Normalize(currPoint - position); // 방향 구하고

	////sprite.setRotation(Utils::Angle(direction)); // 추가 // 이미지가 움직인다

	//position += direction * speed * dt;
	//sprite.setPosition(position); // 추가



	//position += direction * speed * dt;
	//sprite.setPosition(position);

}

void Arrow::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

Enemy* Arrow::MostCloseEnemy(Enemy* enemy)
{
	//Enemy* mostCloseEnemy = nullptr;
	//float minDistance = std::numeric_limits<float>::max();

	//// Get the position of the tower
	//sf::Vector2f towerPosition = GetPosition();

	//// Loop through the enemy pool to find the closest enemy
	//for (const auto& enemy : enemyObjectPool)
	//{
	//	// Check if the enemy is active and within the tower's attack range
	//	if (enemy.IsActive() && IsWithinRange(towerPosition, enemy.GetPosition()))
	//	{
	//		// Calculate the distance between the tower and the enemy
	//		float distance = CalculateDistance(towerPosition, enemy.GetPosition());

	//		// Update the closest enemy if a closer one is found
	//		if (distance < minDistance)
	//		{
	//			minDistance = distance;
	//			mostCloseEnemy = &enemy;
	//		}
	//	}
	//}




	return nullptr;
}
