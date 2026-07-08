#include "featureMatcher.h"
#include <iostream>
#include <vector>


FeatureMatcher::FeatureMatcher() { orbDetector = cv::AKAZE::create(); }

cv::Mat FeatureMatcher::processImage(const cv::Mat &image)
{

  std::vector<cv::KeyPoint> keyPoints;
  cv::Mat descriptors;
  orbDetector->detectAndCompute(image, cv::Mat(), keyPoints, descriptors);

  cv::Mat image_keypoints;
  cv::drawKeypoints(image, keyPoints, image_keypoints, cv::Scalar(0, 255, 0));
  return image_keypoints;
}


cv::Mat FeatureMatcher::matchImages(const cv::Mat &firstImage, const cv::Mat &secondImage)
{
  std::vector<cv::KeyPoint> kp1, kp2;
  cv::Mat desc1, desc2;

  orbDetector->detectAndCompute(firstImage, cv::Mat(), kp1, desc1);
  orbDetector->detectAndCompute(secondImage, cv::Mat(), kp2, desc2);

  cv::BFMatcher bf(cv::NORM_HAMMING, true);
  std::vector<cv::DMatch> matches;
  bf.match(desc1, desc2, matches);

  cv::Mat matched_image;
  cv::drawMatches(firstImage, kp1, secondImage, kp2, matches, matched_image);

  return matched_image;
}

void FeatureMatcher::getPoseDelta(const cv::Mat &firstImage, const cv::Mat &secondImage)
{
  std::vector<cv::KeyPoint> kp1, kp2;
  cv::Mat desc1, desc2;

  orbDetector->detectAndCompute(firstImage, cv::Mat(), kp1, desc1);
  orbDetector->detectAndCompute(secondImage, cv::Mat(), kp2, desc2);

  cv::BFMatcher bf(cv::NORM_HAMMING, true);
  std::vector<cv::DMatch> matches;
  bf.match(desc1, desc2, matches);

  std::vector<cv::Point2f> src_pts, dst_pts;
  for (const auto &match : matches) {
    src_pts.push_back(kp1[match.queryIdx].pt);
    dst_pts.push_back(kp1[match.trainIdx].pt);
  }

  cv::Mat H = cv::findHomography(src_pts, dst_pts, cv::RANSAC, 5.0);

  std::cout << H << std::endl;
}
