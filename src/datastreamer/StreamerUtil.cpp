#include "DataTypes.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <vector>

std::vector<std::filesystem::path> fetchDatasetFiles(const std::filesystem::path &datasetRootDirectory)
{
  std::vector<std::filesystem::path> files;
  const auto datasetPath = datasetRootDirectory / "data";
  if (!(std::filesystem::exists(datasetPath) && std::filesystem::is_directory(datasetPath))) { return files; }

  for (const auto &entry : std::filesystem::directory_iterator(datasetPath)) {
    files.push_back(entry.path());
  }

  std::ranges::sort(files);

  return files;
}


std::vector<TimestampType> fetchTimestamps(const std::filesystem::path &datasetRootDirectory)
{
  std::ifstream timestampFile{ datasetRootDirectory / "timestamps.txt" };
  std::vector<TimestampType> timestamps{};

  for (std::string line; std::getline(timestampFile, line);) {
    std::istringstream lineStream{ line };
    TimestampType timepoint;

    if (lineStream >> std::chrono::parse("%F %T", timepoint)) { timestamps.push_back(timepoint); }
  }

  return timestamps;
}

std::vector<DataPage> fetchDataPages(const std::filesystem::path &datasetRootDirectory)
{

  std::vector<DataPage> dataPages{};
  const std::vector<std::filesystem::path> files = fetchDatasetFiles(datasetRootDirectory);
  const std::vector<TimestampType> timestamps = fetchTimestamps(datasetRootDirectory);

  for (auto &&[time, file] : std::views::zip(timestamps, files)) {
    dataPages.push_back({ .path = file, .timestamp = time });
  }

  return dataPages;
}
