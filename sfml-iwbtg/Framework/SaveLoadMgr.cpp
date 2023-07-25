#include "stdafx.h"
#include "SaveLoadMgr.h"

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
        std::cout << "saved" << std::endl;
    }
    else
    {
        std::cout << "open error" << std::endl;
    }
}

void SaveLoadMgr::LoadGame(const std::string& fileName, std::map<std::string, std::string>& dataMap)
{

}