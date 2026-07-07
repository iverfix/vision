#include "DataStreamer.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

DataStreamer::DataStreamer(std::filesystem::path path) : dataset_path(std::move(path)) { fetchDataset(); }


void DataStreamer::fetchDataset()
{
  // Fetch image files
  std::vector<std::filesystem::path> files;
  if (std::filesystem::exists(dataset_path / "data") && std::filesystem::is_directory(dataset_path / "data")) {
    for (const auto &entry : std::filesystem::directory_iterator(dataset_path / "data")) {
      files.push_back(entry.path());
    }
  }
  std::ranges::sort(files);

  // Fetch timestamps

  std::ifstream timestampFile{ dataset_path / "timestamps.txt" };
  size_t counter{};

  std::string line;
  while (std::getline(timestampFile, line)) {
    std::istringstream lineStream{ line };
    TimestampType timepoint;
    lineStream >> std::chrono::parse("%F %T", timepoint);

    imageFiles.push_back({ .path = files[counter], .timestamp = timepoint });
    ++counter;
  }

  maxImageIndex = imageFiles.size();
}

std::optional<ImageData> DataStreamer::fetchNext()
{

  if (nextImageIndex >= maxImageIndex) { return std::nullopt; }

  auto currentImageMetadata = imageFiles[nextImageIndex];

  auto imageData = cv::imread(dataset_path / "data" / currentImageMetadata.path, cv::IMREAD_GRAYSCALE);

  ++nextImageIndex;
  return ImageData{ .image = imageData, .time = currentImageMetadata.timestamp };
}
