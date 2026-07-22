#include "DataStreamer/ImageStreamer.h"
#include "DataStreamer/DataTypes.h"
#include "StreamerUtil.h"
#include <filesystem>
#include <optional>
#include <vector>

ImageStreamer::ImageStreamer(std::filesystem::path path) : datasetRootDirectory(std::move(path)), imageFiles(fetchDataPages(datasetRootDirectory)) {}

std::optional<ImageData> ImageStreamer::fetchNext()
{

  if (nextImageIndex >= imageFiles.size()) { return std::nullopt; }

  const auto currentImageMetadata = imageFiles.at(nextImageIndex);
  const auto imageData = cv::imread(datasetRootDirectory / "data" / currentImageMetadata.path, cv::IMREAD_GRAYSCALE);

  ++nextImageIndex;
  return ImageData{ .image = imageData, .time = currentImageMetadata.timestamp };
}
