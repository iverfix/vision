#include <chrono>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <optional>
#include <vector>

using TimestampType = std::chrono::sys_time<std::chrono::nanoseconds>;

struct ImageData
{
  cv::Mat image;
  TimestampType time;
};


struct ImageMetaData
{
  std::filesystem::path path;
  TimestampType timestamp;
};

class DataStreamer
{

public:
  explicit DataStreamer(std::filesystem::path path);
  std::optional<ImageData> fetchNext();

private:
  void fetchDataset();
  std::filesystem::path dataset_path{};
  size_t nextImageIndex{};
  size_t maxImageIndex{};
  std::vector<ImageMetaData> imageFiles;
};
