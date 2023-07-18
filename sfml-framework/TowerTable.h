#pragma once
#include "DataTable.h"
#include "Tower.h"
#include <rapidcsv.h>

struct TowerInfo
{
   //. Tower::Types towerType;

    std::string textureId;
    float arrowSpeed = 0.f;
    int damage = 0.f;

};


class TowerTable : public DataTable
{
protected:
    //std::unordered_map< Enemy::Types, EnemyInfo > towerTables;



};

