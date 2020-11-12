#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <string>
#include <vector>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class DataAccess {
    public:

        void Open(std::string fileName = "SaveData.txt");

        void Save() const;

        void SetValue(std::string dataId, std::string dataValue);

        std::string GetValue(std::string dataId) const;

        int Remove(std::string dataId);

        void Print() const;

        int Size() const;

    private:

        const std::string PARENT_DIRECTORY = "./data/";

        fs::path filePath;

        struct DataPoint {
            std::string id;
            std::string value;
        };

        std::vector<DataPoint> dataPoints;

        int IndexFromId(std::string dataId) const;
};

#endif