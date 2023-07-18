#include "stdafx.h"
#include "TileMap.h"
#include "rapidcsv.h"

class SceneDev1;

TileMap::TileMap(const std::string& textureId, const std::string& n)
	: VertexArrayGo(textureId, n)
{
}

TileMap::~TileMap()
{
}

bool TileMap::Load(const std::string& filePath)
{
    rapidcsv::Document map(filePath, rapidcsv::LabelParams(-1, -1));
    sf::Vector2i size = { (int)map.GetColumnCount(), (int)map.GetRowCount() };

    //int texInt = 4;

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            Tile tile;
            tile.x = j;
            tile.y = i;
            tile.texIndex = map.GetCell<int>(j, i);
            tiles.push_back(tile);
        }
    }
    
    sf::Vector2f tileSize = { 90.f, 85.f  };
    sf::Vector2f texSize = { 90.f, 85.f };
    sf::Vector2f texOffsets[4] =
    {
        { 0.f, 0.f },
        { texSize.x, 0.f },
        { texSize.x, texSize.y },
        { 0.f, texSize.y }
    };


    // resize the vertex array to fit the level size
    vertexArray.setPrimitiveType(sf::Quads);
    vertexArray.resize(size.x * size.y * 4);
    sf::Vector2f startPos = { 13.5, 0 };
    sf::Vector2f currPos = startPos;

    //���̼Ҹ�Ʈ�� ���� �߰� //���̼Ҹ�Ʈ�� ���� �߰�
    //���̼Ҹ�Ʈ�� ���� �߰� //���̼Ҹ�Ʈ�� ���� �߰�

    float widthDifference = tileSize.x * 0.5f;
    float heightDifference = tileSize.y * 0.5f;
    float perspective = heightDifference * (tileSize.x / tileSize.y);
    // perspective ���̼� ��Ʈ�� � ���÷� ���� ���� ����

    sf::Vector2f offsets[4] =
    {
        { 0.f, 0.f },
        { tileSize.x, 0.f },
        { tileSize.x, tileSize.y},
        { 0.f, tileSize.y }
    };

    for (int i = 0; i < size.y; ++i)
    {
        for (int j = 0; j < size.x; ++j)
        {
            int tileIndex = size.x * i + j;
            int texIndex = tiles[tileIndex].texIndex;
            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = tileIndex * 4 + k;
                vertexArray[vertexIndex].position = currPos + offsets[k];
                vertexArray[vertexIndex].texCoords = texOffsets[k];
                vertexArray[vertexIndex].texCoords.y += texSize.y * texIndex;
            }
            currPos.x += tileSize.x; // ����
            // currPos.y += heightDifference;
            
        }
        currPos.x = startPos.x;
       
        if (i % 2 == 0)
        {
            currPos.x += widthDifference;
        }

        
        currPos.y += tileSize.y * 0.3025f/*+ (tileSize.y * 0.635f)*/;
        // ����

    } // 0.3025f

    // ������ Ÿ���� �� ����ݾ�

    // ������ Ÿ���ε� ���� ��°� ���ݾ�. 

    return true;
}

sf::Vector2f TileMap::screenToIsoTileCoords(sf::Vector2f screenCoords, sf::Vector2f tile)
{
    //100 / 95

    // Ÿ�ϸ� �ε忡�� ����� ��Ĵ�� �������־����

    //sf::Vector2f startPos = { 0, 0 };
    //sf::Vector2f currPos = startPos;



    float tileXf = static_cast<float>(screenCoords.x) / tile.x; // ���콺���� / Ÿ�� x������
    float tileYf = static_cast<float>(screenCoords.y)
        / tile.y; // ���콺���� / Ÿ�� y������

    //float tileXf = static_cast<float>(screenCoords.x) / tile.x - static_cast<float>(screenCoords.y) / tile.y;
    //float tileYf = static_cast<float>(screenCoords.y) / tile.y + static_cast<float>(screenCoords.y) / tile.y;

    int tileX = static_cast<int>(tileXf);
    int tileY = static_cast<int>(tileYf);

    return sf::Vector2f(tileX, tileY);
}

sf::Vector2f TileMap::screenToIsoTileCenter(sf::Vector2f screenCoords, sf::Vector2f tile)
{
    float tileXf = static_cast<float>(screenCoords.x) / tile.x; // ���콺���� / Ÿ�� x������
    float tileYf = static_cast<float>(screenCoords.y) / tile.y; // ���콺���� / Ÿ�� y������

    int tileX = static_cast<int>(tileXf);
    int tileY = static_cast<int>(tileYf);
  
    // Ÿ�� �߽� ��ǥ ���
    // 1 *

    sf::Vector2f tileCenter(tileX * tile.x / 2.0f, tileY * tile.y / 2.0f);
    return tileCenter;
}
