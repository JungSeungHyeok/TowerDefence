#pragma once
#include "DataTable.h"
#include "Arrow.h"
#include <rapidcsv.h>

struct ArrowInfo
{
    Arrow::Types arrowType;
    std::string textureId;

    float speed;
    float range;
    int damage;

};


class ArrowTable : public DataTable
{
protected:
    std::unordered_map< Arrow::Types, ArrowInfo > arrowTables;

public:
    ArrowTable() : DataTable(DataTable::Ids::Arrow) {};
    virtual ~ArrowTable() override = default;

    virtual bool Load() override;
    virtual void Release() override;
    const ArrowInfo& Get(Arrow::Types id);


};

