#pragma once
#include "Camera/Camera.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>


class FeatureMatcher
{
public:
  FeatureMatcher() = default;
  void getPoseDelta(const cv::Mat &firstImage, const cv::Mat &secondImage, const Camera &camera);

private:
  cv::Ptr<cv::AKAZE> detector{ cv::AKAZE::create() };
  Eigen::Quaterniond rotationState{ Eigen::Quaterniond::Identity() };
};
