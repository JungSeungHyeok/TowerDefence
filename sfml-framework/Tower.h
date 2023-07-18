#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"


// Ÿ���� ��������Ʈ
// �ִϸ��̼� ���� ǥ��

class SoundGo;
class SceneDev1;


//struct Tile
//{
//float arrowSpeed = 0.f;
//int damage = 0.f;
//};

class Tower : public SpriteGo
{
protected:
	AnimationController animation; // �߰�
	sf::Vector2f direction; // �߰�

	bool isInstalled = false;
	bool testHide = true;

	sf::ConvexShape diamond1;
	sf::ConvexShape diamond2;
	sf::ConvexShape diamond3;
	sf::ConvexShape diamond4;
	sf::ConvexShape diamond5;
	sf::ConvexShape diamond6;

	sf::FloatRect diaBounds;

	const float diamondWidth = 35.f;
	const float diamondHeight = 35.f; // ������ ũ��
	

	// bool isHover = false; // ��ġ ������ Ÿ������ �Ǵ�

public:

	Tower(const std::string& textureId = "", const std::string& n = "")
		:SpriteGo(textureId, n) {}

	virtual ~Tower() override { Release(); };

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	// �������� �߰�?

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetSize(); // ������ ���ϰ�
	sf::Vector2f GetCenter(); // Ÿ�� �߾ӿ� ��ġ�ϰ�

	bool Load(const std::string& filePath);

	void InstallTower(const sf::Vector2f& isoTileCoords, const sf::Vector2f& tileSize);

	
	void rotateDiamond(sf::ConvexShape& diamond, float angle);
	//ȸ�� ����

	





	sf::Text text;
	std::function<void()> OnClick;
	std::function<void()> OnEnter;
	std::function<void()> OnExit;


};

