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

