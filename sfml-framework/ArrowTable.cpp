#include "stdafx.h"
#include "ArrowTable.h"

bool ArrowTable::Load()
{
	rapidcsv::Document doc("arrowTables/arrow.csv");
	std::vector<int> ids = doc.GetColumn<int>(0);
	std::vector<std::string> texId = doc.GetColumn<std::string>(1);


    std::vector<int> damageArr = doc.GetColumn<int>(2); // Ãß°¡
    std::vector<int> rangeArr = doc.GetColumn<int>(3);
    std::vector<float> speedArr = doc.GetColumn<float>(4);

    for (int i = 0; i < ids.size(); ++i)
    {
        ArrowInfo info;
        info.arrowType = (Arrow::Types)ids[i];
        info.textureId = texId[i];

        info.damage = damageArr[i];
        info.range = rangeArr[i];
        info.speed = speedArr[i];
        

        arrowTables.insert({ info.arrowType , info });
    }

	return true;
}

void ArrowTable::Release()
{
}

const ArrowInfo& ArrowTable::Get(Arrow::Types id)
{
    return arrowTables[id];
}
