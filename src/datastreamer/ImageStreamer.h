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
  void fetchDataset();
  std::filesystem::path dataset_path{};
  size_t nextImageIndex{};
  size_t maxImageIndex{};
  std::vector<ImageMetaData> imageFiles;
};
