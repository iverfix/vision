#include "Camera/Camera.h"
#include "DataStreamer/ImageStreamer.h"
#include "DataStreamer/OxtsStreamer.h"
#include "FeatureMatcher/FeatureMatcher.h"
#include "StateEstimator/KalmanFilter.h"
#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <print>

constexpr int imageCaptureFrequency = 10;
constexpr int fps = 1000 / imageCaptureFrequency;

int main()
{

  const std::filesystem::path projectRoot = PROJECT_ROOT_DIR;
  const std::filesystem::path datasetPath = projectRoot / "dataset" / "image_data" / "image_00";
  const std::filesystem::path oxtsPath = projectRoot / "dataset" / "image_data" / "oxts";

  ImageStreamer streamer{ datasetPath };
  FeatureMatcher matcher{};
  Camera const camera{ 2, projectRoot / "dataset" };
  OxtsStreamer oxtsStreamer{ oxtsPath };

  std::optional<ImageData> previousImage = streamer.fetchNext();
  std::optional<OxtsData> measurement = oxtsStreamer.fetchNextMeasurement();

  StateVector priorState;
  priorState << Eigen::Vector3d::Zero(), measurement->measurement.velocityBody;


  const StateMatrix priorCovariance = StateMatrix::Identity();
  const auto time = measurement->time;
  std::println("Start time {}", time);
  KalmanFilter filter{ priorState, priorCovariance, measurement->time };
  MeasurementMatrix measurementMatrix = MeasurementMatrix::Zero();
  measurementMatrix.block<3, 3>(0, 3) = Eigen::Matrix3d::Identity();


  while (previousImage.has_value()) {

    const auto currentImage = streamer.fetchNext();

    if (currentImage == std::nullopt) { break; }

    measurement = oxtsStreamer.fetchNextMeasurement();

    const Eigen::Matrix3d measurementNoise = Eigen::Vector3d{ 0.1, 0.1, 0.1 }.asDiagonal();
    const Eigen::Vector3d value = measurement.has_value() ? measurement->measurement.velocityBody : Eigen::Vector3d::Zero();

    auto result = filter.predict(measurement->time);

    filter.update(measurementMatrix, measurementNoise, value, measurement->time);

    std::println("Ground Truth: {}", measurement.value().measurement.orientation);
    std::println("Result: {}", result);

    matcher.getPoseDelta(previousImage->image, currentImage->image, camera);
    // auto processedImage = matcher.processImage(data->image);
    cv::imshow("Our image", previousImage->image);
    cv::waitKey(fps);
    previousImage = currentImage;
  }
  cv::destroyWindow("Our image");
  return 0;
}
