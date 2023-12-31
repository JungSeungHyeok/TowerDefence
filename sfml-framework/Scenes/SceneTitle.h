#pragma once
#include "Scene.h"
#include "UIButton.h"


class SceneTitle : public Scene
{
protected:
	std::map<std::string, bool> mouseOverStates;

	std::vector<SpriteGo*> guidebooks;
	int ImageIndex = 0;
	std::vector<sf::Texture> addImageTextures;
	sf::Sprite addImage;

	sf::Sprite guidebook1;
	sf::Sprite guidebook2;
	sf::Sprite guidebook3;
	sf::Sprite guidebackgrund;
	sf::Sprite SelectRound;

	bool isguideButton = false;

	// 애니메이션을 시작할 때의 버튼 위치와 목표 위치를 정의합니다.

public:
	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

