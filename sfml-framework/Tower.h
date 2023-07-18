#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"


// 타워도 스프라이트
// 애니메이션 상태 표현

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
	AnimationController animation; // 추가
	sf::Vector2f direction; // 추가

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
	const float diamondHeight = 35.f; // 마름모 크기
	

	// bool isHover = false; // 설치 가능한 타일인지 판단

public:

	Tower(const std::string& textureId = "", const std::string& n = "")
		:SpriteGo(textureId, n) {}

	virtual ~Tower() override { Release(); };

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	// 겟포지션 추가?

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;

	sf::Vector2f GetSize(); // 사이즈 구하고
	sf::Vector2f GetCenter(); // 타일 중앙에 설치하고

	bool Load(const std::string& filePath);

	void InstallTower(const sf::Vector2f& isoTileCoords, const sf::Vector2f& tileSize);

	
	void rotateDiamond(sf::ConvexShape& diamond, float angle);
	//회전 보류

	





	sf::Text text;
	std::function<void()> OnClick;
	std::function<void()> OnEnter;
	std::function<void()> OnExit;


};

