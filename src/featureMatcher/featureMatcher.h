#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>


class FeatureMatcher
{
public:
  FeatureMatcher();
  cv::Mat processImage(const cv::Mat &image);
  cv::Mat matchImages(const cv::Mat &firstImage, const cv::Mat &secondImage);
  void getPoseDelta(const cv::Mat &firstImage, const cv::Mat &secondImage);

private:
  cv::Ptr<cv::AKAZE> orbDetector;
};
