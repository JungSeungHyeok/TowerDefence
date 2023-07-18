#pragma once
#include "VertexArrayGo.h"

// 나중에 몹이랑 타워 전방선언?

struct Tile
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
};

// 몬스터는 게임오브젝트에 가깝다 나중에 상속 생각
// 몬스터는 오브젝트 풀 참고 좀비서바이벌 좀비 만드는 부분에 가까움

class TileMap : public VertexArrayGo
{
protected:

public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);

	sf::Vector2f screenToIsoTileCoords(sf::Vector2f screenCoords, sf::Vector2f tile);

	sf::Vector2f screenToIsoTileCenter(sf::Vector2f screenCoords, sf::Vector2f tile);
	// 중심값 반환 추가

	std::vector<Tile> tiles;
};

