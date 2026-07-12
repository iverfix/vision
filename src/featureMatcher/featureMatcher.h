#pragma once
#include "Camera.h"
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>


class FeatureMatcher
{
public:
  FeatureMatcher();
  void getPoseDelta(const cv::Mat &firstImage, const cv::Mat &secondImage, const Camera &camera);

private:
  cv::Ptr<cv::AKAZE> orbDetector;
  double accum1{};
  double accum2{};
  double accum3{};
};
