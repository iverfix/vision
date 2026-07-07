#include <chrono>
#include <filesystem>
#include <opencv2/opencv.hpp>

struct ImageData
{

  cv::Mat image;
  std::chrono::time_point<std::chrono::steady_clock> time;
};

class DataStreamer
{

  explicit DataStreamer(const std::filesystem::path &path);
  ImageData fetchNext();
};
