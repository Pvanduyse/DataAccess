//Submodule file

#include <iostream>
#include <fstream>

#include "DataAccess.h"

int DataAccess::Load(const std::string& filename, const bool overrideCache) {
	UpdateFilename(filename);
	return Load(overrideCache);
}

int DataAccess::Load(const bool overrideCache) {
	if(overrideCache == true) {
		dataset.resize(0);
		return ReadFile(dataset);
	}

	std::vector<DataPoint> fileDataSet;
	if(ReadFile(fileDataSet) == -1) {
		return -1;	
	}

	for(DataPoint data : fileDataSet) {
		SetValue(data.id, data.value);
	}
	return 0;
}

void DataAccess::Save(const std::string& filename, const bool overrideFile) {
	UpdateFilename(filename);
	Save(overrideFile);
}

void DataAccess::Save(const bool overrideFile) {
	std::vector<DataPoint> existingData;
	if(overrideFile == false && fs::exists(filePath) == true) {
		ReadFile(existingData);
		for(DataPoint data : dataset) {
			int index = IndexFromId(data.id, existingData);
			if(index == -1) {
				existingData.push_back(data);
			}
			else {
				existingData.at(index) = data;
			}
		}
	}
	else {
		existingData = dataset;
	}

	if(fs::exists(filePath) == false) {
        fs::create_directories(filePath.parent_path());
	}

    std::ofstream outFile;
    outFile.open(filePath);
    if(outFile.is_open() == false) {
		throw;
    }

    outFile << existingData.size() << std::endl;

	for(DataPoint data : existingData) {
        outFile << data.id << " " << data.value << std::endl;
	}
	outFile.close();
}

void DataAccess::SetValue(const std::string& dataId, const std::string& dataValue) {
    int index = IndexFromId(dataId);
    if(index == -1) {//IndexFromId returns -1 if a data point was not found
        DataPoint newDataPoint;
        newDataPoint.id = dataId;
        newDataPoint.value = dataValue;
        dataset.push_back(newDataPoint);
    }
    else {
        dataset.at(index).value = dataValue;
    }
}

std::string DataAccess::GetValue(const std::string& dataId) const {
    int index = IndexFromId(dataId);
    if(index == -1) {//IndexFromId returns -1 if a data point was not found
        return "ERROR: No data point of ID [" + dataId + "] was found in " + filePath.generic_string();
    }
    return dataset.at(index).value;
}

int DataAccess::Remove(const std::string& dataId) {
    int index = IndexFromId(dataId);
    if(index == -1) {
        return -1;
    }
    dataset.erase(dataset.begin() + index);
    return 0;
}

void DataAccess::Print(bool printIds) const {
    for(DataPoint data : dataset) {
        if(printIds == true){
            std::cout << data.id << " ";
        }
        std::cout << data.value << std::endl;
    }
}

int DataAccess::Size() const {
    return dataset.size();
}

int DataAccess::ReadFile(std::vector<DataPoint>& dataPointVector) const {
    std::ifstream inFile;
    unsigned int size = 0;
    DataPoint newData;
    
    if(fs::exists(filePath) == false) {
		return -1;
	}

	inFile.open(filePath);
	if(inFile.is_open() == false) {
		return -1;
	}

	inFile >> size;
	inFile.ignore();

	for(unsigned int i = 0; i < size; i++) {
		inFile >> newData.id;
		inFile.ignore();
		getline(inFile, newData.value);
		dataPointVector.push_back(newData);
	}

	inFile.close();
	return 0;
}

int DataAccess::IndexFromId(const std::string& dataId) const {
    return IndexFromId(dataId, dataset);
}

int DataAccess::IndexFromId(const std::string& dataId, const std::vector<DataPoint>& dataPointVector) const {
    for(unsigned int i = 0; i < dataPointVector.size(); ++i) {
        if(dataPointVector.at(i).id == dataId) {
            return i;
        }
    }
    return -1;
}

void DataAccess::UpdateFilename(const std::string &filename) {
	filePath.filename() = filename;
	if(filePath.extension() == "") {
		filePath += ".txt";
	}
}
