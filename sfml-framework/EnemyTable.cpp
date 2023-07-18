#include "stdafx.h"
#include "EnemyTable.h"

bool EnemyTable::Load()
{
    // Enemy
    // enemyTables

    rapidcsv::Document doc("enemyTables/Enemy.csv"); // 몬스터 csv 파일
    std::vector<int> ids = doc.GetColumn<int>(0);
    std::vector<std::string> texId = doc.GetColumn<std::string>(1);
    std::vector<float> speedArr = doc.GetColumn<float>(2);
    std::vector<int> hpArr = doc.GetColumn<int>(3);

    for (int i = 0; i < ids.size(); ++i)
    {
        EnemyInfo info;
        info.enemyType = (Enemy::Types)ids[i];
        info.textureId = texId[i];
        info.speed = speedArr[i];
        info.maxHp = hpArr[i];

        enemyTables.insert({ info.enemyType , info});
    }

    return true;
}

void EnemyTable::Release()
{
    //for (auto tables : enemyTables)
    //{
    //    
    //}
}

const EnemyInfo& EnemyTable::Get(Enemy::Types id)
{
	return enemyTables[id];
}
