#include "stdafx.h"
#include "DataTableMgr.h"
#include "StringTable.h"
#include "EnemyTable.h"
#include "TowerTable.h"
#include "ArrowTable.h"

void DataTableMgr::LoadAll()
{
	tables.insert({ DataTable::Ids::String, new StringTable() });
	tables.insert({ DataTable::Ids::Enemy, new EnemyTable() });
	tables.insert({ DataTable::Ids::Tower, new TowerTable() }); // 타워 테이블 추가
	tables.insert({ DataTable::Ids::Arrow, new ArrowTable() }); // 화살 테이블

	//tables.insert({ DataTable::Ids::Enemy, new TowerTable() });


	for (auto pair : tables)
	{
		if (!pair.second->Load())
		{
			std::cout << "ERR: DATA TABLE LOAD FAIL" << std::endl;
			exit(-1);
		}
	}
}

void DataTableMgr::ReleaseAll()
{
	for (auto pair : tables)
	{
		//pair.second->Release();
		delete pair.second;
	}
	tables.clear();
}
