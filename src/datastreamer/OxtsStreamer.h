#pragma once
#include "DataTypes.h"
#include <filesystem>

class OxtsStreamer
{
public:
  explicit OxtsStreamer(std::filesystem::path path);
  void parseOxtsFile();

private:
  std::filesystem::path datasetRootDirectory;
  std::vector<DataPage> files;
};
