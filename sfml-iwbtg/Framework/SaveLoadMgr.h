#pragma once
#include "Singleton.h"

class SaveLoadMgr : public Singleton<SaveLoadMgr>
{
	friend Singleton<SaveLoadMgr>;

protected:
	SaveLoadMgr();
	virtual ~SaveLoadMgr() override = default;

	std::map<std::string, std::string> defaultMap;
	std::vector<std::string> fileNames;
	const std::string* currentFileName = nullptr;
	
public:
	void SaveGame(const std::string& fileName, const std::map<std::string, std::string>& dataMap);
	void LoadGame(const std::string& fileName, std::map<std::string, std::string>& dataMap);

	void SetCurrentFileName(const std::string& fileName);
	const std::string& GetCurrentFileName();
};

#define SAVELOAD_MGR (SaveLoadMgr::Instance())