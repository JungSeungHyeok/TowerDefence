#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "Enemy.h"
#include "ObjectPool.h"
#include "Arrow.h"
#include "EnemyTable.h"

// Ÿ���� ��������Ʈ
// �ִϸ��̼� ���� ǥ��

class SoundGo;
class SceneDev1;
class GameObject;


class Tower : public SpriteGo
{
public:
	enum class Types
	{
		ArcherTower1,
		ArcherTower2,
		ArcherTower3,

		WizardTower1,
		WizardTower2,
		WizardTower3,
	};
	static const int TotalTypes = 6;


protected:
	AnimationController animation; // �߰�
	Types towerType;

	ObjectPool<Enemy> poolEnemys;
	ObjectPool<Arrow> poolArrows;

	sf::Vector2f direction; // �߰�
	float speed = 1000.f;

public:

	Tower(const std::string& textureId = "", const std::string& n = "")
		:SpriteGo(textureId, n) {}

	virtual ~Tower() override { Release(); };

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetSize(); // ������ ���ϰ�
	sf::Vector2f GetCenter(); // Ÿ�� �߾ӿ� ��ġ�ϰ�

	bool Load(const std::string& filePath);

	void SetType(Types t);
	Types GetType() const;

	

	void TowerAttack(const sf::Vector2f& position, const sf::Vector2f& look, float dt);

	
	// const TowerInfo& tower, const MonsterInfo& monster)



	//void InstallTower(const sf::Vector2f& isoTileCoords, const sf::Vector2f& tileSize);

	//void rotateDiamond(sf::ConvexShape& diamond, float angle);
	////ȸ�� ����

	//sf::Text text;
	//std::function<void()> OnClick;
	//std::function<void()> OnEnter;
	//std::function<void()> OnExit;
	// ����

};

