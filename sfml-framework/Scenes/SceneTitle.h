#pragma once
#include "Scene.h"
#include "UIButton.h"

//class SpriteGo;

class SceneTitle : public Scene
{
protected:
	std::map<std::string, bool> mouseOverStates;
	//SpriteGo* sprite;
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

