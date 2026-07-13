#pragma once
#include "DataTypes.h"
#include <filesystem>
#include <vector>

std::vector<DataPage> fetchDataPages(const std::filesystem::path &datasetRootDirectory);
