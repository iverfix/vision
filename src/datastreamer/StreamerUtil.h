#pragma once
#include "DataTypes.h"
#include <filesystem>
#include <vector>

std::vector<std::filesystem::path> fetchDatasetFiles(const std::filesystem::path &datasetRootDirectory);


std::vector<TimestampType> fetchTimestamps(const std::filesystem::path &datasetRootDirectory);
