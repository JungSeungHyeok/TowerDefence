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

    //�ϴ� 3����
};


class EnemyTable : public DataTable
{
protected:
    std::unordered_map< Enemy::Types, EnemyInfo > enemyTables;

    // ������ ���� �����ϰڴٴ°ǵ�

public:
    EnemyTable() : DataTable(DataTable::Ids::Enemy) {};
    virtual ~EnemyTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;
    const EnemyInfo& Get(Enemy::Types id);


};

