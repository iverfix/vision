#pragma once
#include "Camera/Camera.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>


struct OdometryImagePair
{
  cv::Mat previousFrame;
  cv::Mat currentFrame;
};

class FeatureMatcher
{
public:
  FeatureMatcher() = default;
  void getPoseDelta(const OdometryImagePair &imagePair, const Camera &camera);

private:
  cv::Ptr<cv::AKAZE> detector{ cv::AKAZE::create() };
  Eigen::Quaterniond rotationState{ Eigen::Quaterniond::Identity() };
};
