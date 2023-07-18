#include "stdafx.h"
#include "Tower.h"

#include "InputMgr.h"
#include "TileMap.h" // 7-17 리셋부분 참고 추가

void Tower::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
}


void Tower::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	//보류
}


void Tower::Init()
{


	//RESOURCE_MGR.Load(ResourceTypes::Texture, "Towers/Archer/archer_level_1.png");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Bow_Idle.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Bow_Arrow.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/Archer_Tower.csv");

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Bow_Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Bow_Arrow.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/Archer_Tower.csv"));

	animation.SetTarget(&sprite);
	SetOrigin(Origins::BC);


	// 여기서부터 마름모 하드코딩



	diamond1.setPointCount(4);
	diamond1.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
	diamond1.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
	diamond1.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
	diamond1.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
	diamond1.setFillColor(sf::Color::Green);
	diamond1.setPosition(569, 160);

	diamond2.setPointCount(4);
	diamond2.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
	diamond2.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
	diamond2.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
	diamond2.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
	diamond2.setFillColor(sf::Color::Green);
	diamond2.setPosition(838, 211);

	diamond3.setPointCount(4);
	diamond3.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
	diamond3.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
	diamond3.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
	diamond3.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
	diamond3.setFillColor(sf::Color::Green);
	diamond3.setPosition(613, 340);

	diamond4.setPointCount(4);
	diamond4.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
	diamond4.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
	diamond4.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
	diamond4.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
	diamond4.setFillColor(sf::Color::Green);
	diamond4.setPosition(883, 392);

	diamond5.setPointCount(4);
	diamond5.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
	diamond5.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
	diamond5.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
	diamond5.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
	diamond5.setFillColor(sf::Color::Green);
	diamond5.setPosition(748, 469);

	diamond6.setPointCount(4);
	diamond6.setPoint(0, sf::Vector2f(0.f, diamondHeight / 2.f));
	diamond6.setPoint(1, sf::Vector2f(diamondWidth / 2.f, 0.f));
	diamond6.setPoint(2, sf::Vector2f(diamondWidth, diamondHeight / 2.f));
	diamond6.setPoint(3, sf::Vector2f(diamondWidth / 2.f, diamondHeight));
	diamond6.setFillColor(sf::Color::Green);
	diamond6.setPosition(1063, 442);
}

void Tower::Reset()
{
	

	//animation.Play("Bow_Idle");
	SetOrigin(origin);
	SetPosition({ 100, 200 }); // 셋 포지션을 타일 클릭 가운데타워
	sortLayer = 6;
	//SetActive(false);
}

void Tower::Update(float dt)
{
	animation.Update(dt);

	bool isHover = false;
	bool prevHover = isHover;


	TileMap tile;

	sf::Vector2f tileSize = { 90, 85 };
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mousePosition = INPUT_MGR.GetMousePos();
	sf::Vector2f uiMousePos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	sf::Vector2f isoTileCoords = tile.screenToIsoTileCoords(uiMousePos, sf::Vector2f(tileSize.x, tileSize.y));

	//if (!prevHover && INPUT_MGR.GetMouseButtonDown(sf::Mouse::Right))
	//{
	//	
	//	animation.Play("Archer_Tower");

	//	SetPosition(563, 140);


	//	//InstallTower(isoTileCoords, tileSize);

	//}






	// 마름모 충돌체크

	bool isColliding = true;

	{
		diaBounds = diamond1.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(561, 134);

			animation.Play("Bow_Idle");
			SetPosition(530, 134);

			std::cout << "충돌체크1" << std::endl;
		}
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::T))
		{
			testHide = !testHide;
		}
	}

	{
		diaBounds = diamond2.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(832, 185);

			std::cout << "충돌체크2" << std::endl;
		}
	}

	{
		diaBounds = diamond3.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(607, 313);

			std::cout << "충돌체크3" << std::endl;
		}
	}

	{
		diaBounds = diamond4.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(877, 365);

			std::cout << "충돌체크4" << std::endl;
		}
	}

	{
		diaBounds = diamond5.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(742, 442);

			std::cout << "충돌체크5" << std::endl;
		}
	}

	{
		diaBounds = diamond6.getGlobalBounds();
		isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y);

		if (isColliding == diaBounds.contains(uiMousePos.x, uiMousePos.y)
			&& INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
		{
			animation.Play("Archer_Tower");
			SetPosition(1057, 416);

			std::cout << "충돌체크6" << std::endl;
		}
	}


}

void Tower::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	if (testHide)
	{
		window.draw(diamond1);
		window.draw(diamond2);
		window.draw(diamond3);
		window.draw(diamond4);
		window.draw(diamond5);
		window.draw(diamond6);
	}
}

sf::Vector2f Tower::GetSize()
{
	sf::Vector2f size = {45, 57};


	//size.x = sprite.getGlobalBounds().width;
	//size.y = sprite.getGlobalBounds().height;

	return size;

	// return sf::Vector2f();
}

sf::Vector2f Tower::GetCenter()
{
	sf::Vector2f size = { 45, 57 };
	sf::Vector2f center;

	center.x = size.x + size.y / 2;
	center.y = size.x + size.y / 2;

	return center;

	// return sf::Vector2f();
}

bool Tower::Load(const std::string& filePath)
{
	//SetPosition(0, 100);

	return true;
}

void Tower::InstallTower(const sf::Vector2f& isoTileCoords, const sf::Vector2f& tileSize)
{

	if (!isInstalled)
	{
		sf::Vector2f tileCenter(isoTileCoords.x * tileSize.x + tileSize.x / 2.0f, isoTileCoords.y * tileSize.y + tileSize.y / 2.0f);
		SetPosition(tileCenter);
		isInstalled = true;
		// 타일 중심 설치 추가


		//SetPosition(isoTileCoords.x * tileSize.x, isoTileCoords.y * tileSize.y);
		//isInstalled = true;
	}
}

void Tower::rotateDiamond(sf::ConvexShape& diamond, float angle)
{

	sf::Vector2f center(diamondWidth / 2.f, diamondHeight / 2.f);
	diamond.setOrigin(center);
	diamond.setRotation(angle);
	
}
