#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"

class Object : public SpriteGo
{
public:
	enum class Types
	{
		Crystal1,
		Crystal2,
		Crystal3,
		Stone1,
		Stone2,
		Stone3,
		Stone4,
		Tree1,
		Tree2,
		Stone_Ground1,
		Stone_Ground2,
		Stone_Ground3,
		Stone_Ground4,
		Grass_Deco1, Grass_Deco2, Grass_Deco3, Grass_Deco4, Grass_Deco5,
		Grass_Deco6, Grass_Deco7, Grass_Deco8, Grass_Deco9,
	};
	static const int TotalTypes = 22;

protected:
	Types objectType;
	sf::Vector2f position;

public:

	Object(const std::string& textureId = "", const std::string& n = "")
		:SpriteGo(textureId, n) {}
	virtual ~Object() override { Release(); };

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f& p);

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	bool Load(const std::string& filePath);

	void SetType(Types t);
	Types GetType() const;



};

