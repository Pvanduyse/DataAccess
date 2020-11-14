//Submodule file

#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class DataAccess {
    public:

        void Open(const std::string& fileName = "SaveData.txt");

        void Save() const;

        void SetValue(const std::string& dataId, const std::string& dataValue);

        std::string GetValue(const std::string& dataId) const;

        int Remove(const std::string& dataId);

        void Print(bool printIds = false) const;

        int Size() const;

    private:

        const std::string PARENT_DIRECTORY = "./data/";

        fs::path filePath;

        struct DataPoint {
            std::string id;
            std::string value;
        };

        std::vector<DataPoint> dataPoints;

        int IndexFromId(const std::string& dataId) const;
};

#endif
