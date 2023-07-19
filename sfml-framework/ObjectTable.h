#pragma once
#include "DataTable.h"
#include "Object.h"
#include <rapidcsv.h>

struct ObjectInfo
{
	Object::Types objectType;
	std::string textureId;
};

class ObjectTable : public DataTable
{
protected:
	std::unordered_map< Object::Types, ObjectInfo > objectTables;

public:
	ObjectTable() : DataTable(DataTable::Ids::Object) {};
	virtual ~ObjectTable() override = default;

	virtual bool Load() override;
	virtual void Release() override;
	const ObjectInfo& Get(Object::Types id);

};

