#pragma once
#include "Singleton.h"
#include "DataTable.h"

class DataTableMgr : public Singleton<DataTableMgr>
{
protected:
	std::unordered_map<DataTable::Ids, DataTable*> tables;

	DataTableMgr(const DataTableMgr& other) = delete;
	bool operator==(const DataTableMgr& other) const = delete;

public:
	DataTableMgr() = default;
	virtual ~DataTableMgr() { ReleaseAll(); }

	void LoadAll();
	void ReleaseAll();
	
	template <typename T>
	T* Get(DataTable::Ids id) const;
};

template<typename T>
inline T* DataTableMgr::Get(DataTable::Ids id) const
{
	auto find = tables.find(id);
	if (find == tables.end())
		return nullptr;
	return dynamic_cast<T*>(find->second);
	// 펄스트 키값 ID같은거 ex)0,1,2,3,4
	// 
	// 세컨드는 벨류 ex) 스피드, 체력,
}

#define DATATABLE_MGR (DataTableMgr::Instance())
