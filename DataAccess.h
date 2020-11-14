//Submodule file

#ifndef DATAACCESS_H
#define DATAACCESS_H

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class DataAccess {
	public:

		int Load(const std::string& fileName, const bool overrideCache = false);

		int Load(const bool overrideCache = false);

		void Save(const std::string& fileName, const bool overrideFile = false);
		
		void Save(const bool overrideFile = false);

		void SetValue(const std::string& dataId, const std::string& dataValue);

		std::string GetValue(const std::string& dataId) const;

		int Remove(const std::string& dataId);

		void Print(bool printIds = false) const;

		int Size() const;

	private:

		fs::path filePath ="./data/SaveData.txt";

		struct DataPoint {
			std::string id;
			std::string value;
		};

		std::vector<DataPoint> dataset;

		int ReadFile(std::vector<DataPoint>& dataPointVector) const;

		int IndexFromId(const std::string& dataId) const;

		int IndexFromId(const std::string& dataId, const std::vector<DataPoint>& dataPointVector) const;

		void UpdateFilename(const std::string& filename);
};

#endif
