#pragma once
#include "DataTable.h"
#include "Enemy.h"
#include <rapidcsv.h>

struct EnemyInfo
{
    Enemy::Types enemyType;
    std::string textureId;

    float speed;
    int maxHp;
    int hp;

    //일단 3개만
};


class EnemyTable : public DataTable
{
protected:
    std::unordered_map< Enemy::Types, EnemyInfo > enemyTables;

    // 정보에 따라서 저장하겠다는건데

public:
    EnemyTable() : DataTable(DataTable::Ids::Enemy) {};
    virtual ~EnemyTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;
    const EnemyInfo& Get(Enemy::Types id);


};

