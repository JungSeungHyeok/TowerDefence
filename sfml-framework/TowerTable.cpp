#include "stdafx.h"
#include "TowerTable.h"

bool TowerTable::Load()
{
    // 인트 인트 플로트 인트

    rapidcsv::Document doc("towerTables/Tower.csv"); // 타워 csv파일
    std::vector<int> ids = doc.GetColumn<int>(0);
    std::vector<std::string> texId = doc.GetColumn<std::string>(1);

    std::vector<int> damageArr = doc.GetColumn<int>(2); // 변경
    std::vector<int> rangeArr = doc.GetColumn<int>(3);
    std::vector<int> arrowSpeedArr = doc.GetColumn<int>(4);
    std::vector<float> attackRateArr = doc.GetColumn<float>(5);
    std::vector<int> priceArr = doc.GetColumn<int>(6);

    for (int i = 0; i < ids.size(); ++i)
    {
        TowerInfo info;
        info.towerType = (Tower::Types)ids[i];
        info.textureId = texId[i];
        info.damage = damageArr[i];
        info.range = rangeArr[i];
        info.arrowSpeed = arrowSpeedArr[i];
        info.attackRate = attackRateArr[i];
        //info.price = priceArr[i];

        towerTables.insert({ info.towerType , info });
    }

    return true;
}

void TowerTable::Release()
{
}

const TowerInfo& TowerTable::Get(Tower::Types id)
{
    return towerTables[id];
}
