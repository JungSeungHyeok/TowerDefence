#include "stdafx.h"
#include "ObjectTable.h"

bool ObjectTable::Load()
{
    rapidcsv::Document doc("objectTables/Object.csv"); // 몬스터 csv 파일
    std::vector<int> ids = doc.GetColumn<int>(0);
    std::vector<std::string> texId = doc.GetColumn<std::string>(1);


    for (int i = 0; i < ids.size(); ++i)
    {
        ObjectInfo info;
        info.objectType = (Object::Types)ids[i];
        info.textureId = texId[i];

        objectTables.insert({ info.objectType , info });
    }

    return true;
}

void ObjectTable::Release()
{
}

const ObjectInfo& ObjectTable::Get(Object::Types id)
{
    return objectTables[id];
}

