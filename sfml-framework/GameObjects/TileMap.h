#pragma once
#include "VertexArrayGo.h"

// ���߿� ���̶� Ÿ�� ���漱��?

struct Tile
{
	int x = 0;
	int y = 0;
	int texIndex = 0;
};

// ���ʹ� ���ӿ�����Ʈ�� ������ ���߿� ��� ����
// ���ʹ� ������Ʈ Ǯ ���� ���񼭹��̹� ���� ����� �κп� �����

class TileMap : public VertexArrayGo
{
protected:

public:
	TileMap(const std::string& textureId = "", const std::string& n = "");
	virtual ~TileMap() override;

	bool Load(const std::string& filePath);

	sf::Vector2f screenToIsoTileCoords(sf::Vector2f screenCoords, sf::Vector2f tile);

	sf::Vector2f screenToIsoTileCenter(sf::Vector2f screenCoords, sf::Vector2f tile);
	// �߽ɰ� ��ȯ �߰�

	std::vector<Tile> tiles;
};

