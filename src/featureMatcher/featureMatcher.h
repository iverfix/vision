#pragma once
#include "Camera.h"
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>


class FeatureMatcher
{
public:
  FeatureMatcher();
  cv::Mat processImage(const cv::Mat &image);
  cv::Mat matchImages(const cv::Mat &firstImage, const cv::Mat &secondImage);
  void getPoseDelta(const cv::Mat &firstImage, const cv::Mat &secondImage);
  void getPoseDelta2(const cv::Mat &firstImage, const cv::Mat &secondImage, const Camera &camera);

private:
  cv::Ptr<cv::ORB> orbDetector;
};
