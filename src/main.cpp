#include "Camera.h"
#include "ImageStreamer.h"
#include "OxtsStreamer.h"
#include "featureMatcher.h"
#include <opencv2/opencv.hpp>

constexpr int imageCaptureFrequency = 10;
constexpr int fps = 1000 / imageCaptureFrequency;

int main()
{

  std::filesystem::path projectRoot = PROJECT_ROOT_DIR;
  std::filesystem::path datasetPath = projectRoot / "dataset" / "image_data" / "image_00";

  ImageStreamer streamer{ datasetPath };
  FeatureMatcher matcher{};
  Camera camera{ 0, projectRoot / "dataset" };
  OxtsStreamer oxtsStreamer{ datasetPath };


  auto previousImage = streamer.fetchNext();

  while (previousImage.has_value()) {

    auto currentImage = streamer.fetchNext();

    oxtsStreamer.fetchNextMeasurement();

    matcher.getPoseDelta(previousImage->image, currentImage->image, camera);
    // auto processedImage = matcher.processImage(data->image);
    cv::imshow("Our image", previousImage->image);
    cv::waitKey(fps);
    previousImage = currentImage;
  }
  cv::destroyWindow("Our image");
  return 0;
}
