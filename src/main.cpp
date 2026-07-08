#include "Camera.h"
#include "DataStreamer.h"
#include "featureMatcher.h"
#include <opencv2/opencv.hpp>

constexpr int imageCaptureFrequency = 10;
constexpr int fps = 1000 / imageCaptureFrequency;

int main()
{

  std::filesystem::path projectRoot = PROJECT_ROOT_DIR;
  std::filesystem::path datasetPath = projectRoot / "dataset" / "image_data" / "image_00";

  DataStreamer streamer{ datasetPath };
  FeatureMatcher matcher{};
  Camera camera{ 0, projectRoot / "dataset" };


  auto previousImage = streamer.fetchNext();

  while (previousImage.has_value()) {

    auto currentImage = streamer.fetchNext();
    auto processedImage = matcher.matchImages(previousImage->image, currentImage->image);

    matcher.getPoseDelta2(previousImage->image, currentImage->image, camera);
    // auto processedImage = matcher.processImage(data->image);
    cv::imshow("Our image", processedImage);
    cv::waitKey(fps);
    previousImage = currentImage;
  }
  cv::destroyWindow("Our image");
  return 0;
}
