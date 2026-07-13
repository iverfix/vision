#include "ImageStreamer.h"
#include "StreamerUtil.h"
#include <DataTypes.h>
#include <filesystem>
#include <optional>
#include <vector>

ImageStreamer::ImageStreamer(std::filesystem::path path) : dataset_path(std::move(path)) { fetchDataset(); }


void ImageStreamer::fetchDataset()
{
  const auto files = fetchDatasetFiles(dataset_path);
  const std::vector<TimestampType> timestamps = fetchTimestamps(dataset_path);

  for (auto &&[time, file] : std::views::zip(timestamps, files)) {
    imageFiles.push_back({ .path = file, .timestamp = time });
  }

  maxImageIndex = imageFiles.size();
}

std::optional<ImageData> ImageStreamer::fetchNext()
{

  if (nextImageIndex >= maxImageIndex) { return std::nullopt; }

  const auto currentImageMetadata = imageFiles[nextImageIndex];

  const auto imageData = cv::imread(dataset_path / "data" / currentImageMetadata.path, cv::IMREAD_GRAYSCALE);

  ++nextImageIndex;
  return ImageData{ .image = imageData, .time = currentImageMetadata.timestamp };
}
