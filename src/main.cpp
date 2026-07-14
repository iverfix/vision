#include "Camera.h"
#include "ImageStreamer.h"
#include "OxtsStreamer.h"
#include "featureMatcher.h"
#include <opencv2/opencv.hpp>
#include <print>

constexpr int imageCaptureFrequency = 10;
constexpr int fps = 1000 / imageCaptureFrequency;

int main()
{

  std::filesystem::path projectRoot = PROJECT_ROOT_DIR;
  std::filesystem::path datasetPath = projectRoot / "dataset" / "image_data" / "image_00";
  std::filesystem::path oxtsPath = projectRoot / "dataset" / "image_data" / "oxts";

  ImageStreamer streamer{ datasetPath };
  FeatureMatcher matcher{};
  Camera camera{ 2, projectRoot / "dataset" };
  OxtsStreamer oxtsStreamer{ oxtsPath };


  std::optional<ImageData> previousImage = streamer.fetchNext();

  while (previousImage.has_value()) {

    const auto currentImage = streamer.fetchNext();

    if (currentImage == std::nullopt) { break; }

    const auto measurement = oxtsStreamer.fetchNextMeasurement();

    std::println("Ground Truth: {}", measurement.value().measurement.orientation);

    matcher.getPoseDelta(previousImage->image, currentImage->image, camera);
    // auto processedImage = matcher.processImage(data->image);
    cv::imshow("Our image", previousImage->image);
    cv::waitKey(fps);
    previousImage = currentImage;
  }
  cv::destroyWindow("Our image");
  return 0;
}
