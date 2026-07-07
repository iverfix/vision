#include "DataStreamer.h"
#include <opencv2/opencv.hpp>

constexpr int imageCaptureFrequency = 10;
constexpr int fps = 1000 / imageCaptureFrequency;

int main()
{

  std::filesystem::path projectRoot = PROJECT_ROOT_DIR;
  std::filesystem::path datasetPath = projectRoot / "dataset" / "image_data" / "image_00";

  DataStreamer streamer{ datasetPath };

  auto data = streamer.fetchNext();

  while (data.has_value()) {

    cv::imshow("Our image", data->image);
    cv::waitKey(fps);
    data = streamer.fetchNext();
  }
  cv::destroyWindow("Our image");
  return 0;
}
