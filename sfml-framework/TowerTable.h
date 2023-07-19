#pragma once
#include "DataTable.h"
#include "Tower.h"
#include <rapidcsv.h>

struct TowerInfo
{
    Tower::Types towerType;
    std::string textureId;

    int damage;
    int range;
    float attackRate;
    int price;

    // float arrowSpeed = 0.f;
    //float attackTimer = 0.f;

};

class TowerTable : public DataTable
{
protected:
    std::unordered_map< Tower::Types, TowerInfo > towerTables;

public:
    TowerTable() : DataTable(DataTable::Ids::Tower) {};
    virtual ~TowerTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;
    const TowerInfo& Get(Tower::Types id);



};

