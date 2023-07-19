#include "stdafx.h"
#include "ArrowTable.h"

bool ArrowTable::Load()
{
	rapidcsv::Document doc("arrowTables/arrow.csv");
	std::vector<int> ids = doc.GetColumn<int>(0);
	std::vector<std::string> texId = doc.GetColumn<std::string>(1);


    for (int i = 0; i < ids.size(); ++i)
    {
        ArrowInfo info;
        info.arrowType = (Arrow::Types)ids[i];
        info.textureId = texId[i];

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
