#pragma once
#include "NavigationTypes/Types.h"
#include <filesystem>
#include <optional>

class OxtsStreamer
{
public:
  explicit OxtsStreamer(std::filesystem::path path);
  std::optional<OxtsData> fetchNextMeasurement();

private:
  static std::optional<OxtsMeasurement> parseOxtsFile(const std::filesystem::path &path);
  std::filesystem::path datasetRootDirectory;
  std::vector<DataPage> files;
  size_t nextImageIndex{};
};
