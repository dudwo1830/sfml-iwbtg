#include "stdafx.h"
#include "SaveLoadMgr.h"

SaveLoadMgr::SaveLoadMgr()
{
    fileNames.push_back("Save001.sav");
    fileNames.push_back("Save002.sav");
    fileNames.push_back("Save003.sav");

    defaultMap["SceneId"] = "0";
    defaultMap["PositionX"] = "0";
    defaultMap["PositionY"] = "0";
    defaultMap["DeathCount"] = "0";
}

void SaveLoadMgr::SaveGame(const std::string& fileName, const std::map<std::string, std::string>& dataMap)
{
    std::ofstream outFile(fileName, std::ios::binary | std::ios::out);
    if (outFile.is_open())
    {
        for (const auto& data : dataMap)
        {
            outFile << data.first << " " << data.second << std::endl;
        }

        outFile.close();
        std::cout << *currentFileName << " Saved" << std::endl;
    }
    else
    {
        std::cout << *currentFileName << " Save Error" << std::endl;
    }
}

void SaveLoadMgr::LoadGame(const std::string& fileName, std::map<std::string, std::string>& dataMap)
{
    std::ifstream inFile(fileName, std::ofstream::binary);
    if (inFile.is_open())
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            std::istringstream iss(line);
            std::string key;
            std::string value;
            iss >> key >> value;
            dataMap[key] = value;
        }
        inFile.close();
        std::cout << *currentFileName << " Loaded" << std::endl;
    }
    else
    {
        std::cout << *currentFileName << " Load Error" << std::endl;
        SaveGame(fileName, defaultMap);
        dataMap = defaultMap;
        return;
    }
}

void SaveLoadMgr::SetCurrentFileName(const std::string& fileName)
{
    for (auto& fn : fileNames)
    {
        if (fn == fileName)
        {
            currentFileName = &fn;
            break;
        }
    }
}

const std::string& SaveLoadMgr::GetCurrentFileName()
{
    return *currentFileName;
}
