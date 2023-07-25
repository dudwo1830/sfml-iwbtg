#pragma once
#include "Singleton.h"

class SaveLoadMgr : public Singleton<SaveLoadMgr>
{
	friend Singleton<SaveLoadMgr>;

protected:
	SaveLoadMgr() = default;
	virtual ~SaveLoadMgr() override = default;

	std::string* currentFileName = nullptr;
public:
	void SaveGame(const std::string& fileName, const std::map<std::string, std::string>& dataMap);
	void LoadGame(const std::string& fileName, std::map<std::string, std::string>& dataMap);

	const std::string& GetCurrentFileName() { return *currentFileName; }
};

#define SAVELOAD_MGR (SaveLoadMgr::Instance())