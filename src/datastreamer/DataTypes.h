#pragma once
#include <chrono>
#include <filesystem>
#include <opencv2/core/mat.hpp>

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
