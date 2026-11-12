#include "Config.h"

std::string jsonTemplate = R"({
    "gamertag": "Durangler",
    "gamerscore": 0,
    "keyboard": {
        "WM": 87,
        "AM": 65,
        "SM": 83,
        "DM": 68,
        "A": 90,
        "B": 88,
        "X": 67,
        "Y": 86,
        "Up": 26,
        "Down": 28,
        "Left": 25,
        "Right": 27,
        "Menu": 13,
        "View": 27,
        "LeftThumb": 160,
        "RightThumb": 161,
        "LeftShoulder": 162,
        "RightShoulder": 163,
        "LeftTrigger": 1,
        "RightTrigger": 2
    }
})";

bool wd::common::Config::parse()
{
    try
    {
        /**
         * @brief Check if the file exists, and read the config, 
         * if it doesnt exist, then use the template.
         * @note oop, forgot to open it - CT5
         */
        if (!pDirectory->fileExists("winDurango.json")) {
            pFile = pDirectory->CreateFile("winDurango.json");
            pFile->open();
            pFile->write(jsonTemplate);
        } else {
            pFile = std::make_shared<wd::impl::winrt::interfaces::storage::WinRTFile>(
                pDirectory->dirpath() / std::filesystem::path("winDurango.json"));
            pFile->open();
        }
        
        std::string jsonData = pFile->read();
        data = nlohmann::json::parse(jsonData);
        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
    catch (...)
    {
        return false;
    }
}

const nlohmann::json& wd::common::Config::jsonData() 
{ 
    return data; 
}

const nlohmann::json &wd::common::Config::operator[](std::string node)
{
    return data[node];
}
