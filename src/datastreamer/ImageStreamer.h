#pragma once
#include <DataTypes.h>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <optional>
#include <vector>

class ImageStreamer
{

public:
  explicit ImageStreamer(std::filesystem::path path);
  std::optional<ImageData> fetchNext();

private:
  std::filesystem::path datasetRootDirectory;
  std::vector<DataPage> imageFiles;
  size_t nextImageIndex{};
};
