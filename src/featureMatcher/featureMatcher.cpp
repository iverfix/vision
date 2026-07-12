#include "featureMatcher.h"
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include <print>
#include <vector>

constexpr float KNN_MATCH_RATIO = 0.8;

FeatureMatcher::FeatureMatcher() { orbDetector = cv::AKAZE::create(); }

void FeatureMatcher::getPoseDelta(const cv::Mat &firstImage, const cv::Mat &secondImage, const Camera &camera)
{
  std::vector<cv::KeyPoint> kp1;
  std::vector<cv::KeyPoint> kp2;
  cv::Mat desc1;
  cv::Mat desc2;

  orbDetector->detectAndCompute(firstImage, cv::Mat(), kp1, desc1);
  orbDetector->detectAndCompute(secondImage, cv::Mat(), kp2, desc2);

  cv::BFMatcher matcher(cv::NORM_HAMMING);
  std::vector<std::vector<cv::DMatch>> matches;
  matcher.knnMatch(desc1, desc2, matches, 2);

  std::vector<cv::Point2f> src_pts;
  std::vector<cv::Point2f> dst_pts;
  for (auto &match : matches) {
    const cv::DMatch &first = match[0];
    const float distance1 = match[0].distance;
    const float distance2 = match[1].distance;
    if (distance1 < KNN_MATCH_RATIO * distance2) {
      src_pts.push_back(kp1[first.queryIdx].pt);
      dst_pts.push_back(kp2[first.trainIdx].pt);
    }
  }

  cv::Mat K_cv;
  cv::Mat mask;

  cv::eigen2cv(camera.getCameraMatrix(), K_cv);

  const cv::Mat EssentialMatrix = cv::findEssentialMat(src_pts, dst_pts, K_cv, cv::RANSAC, 0.999, 1.0, 1000, mask);

  cv::Mat rotation;
  cv::Mat translation;
  cv::recoverPose(EssentialMatrix, src_pts, dst_pts, K_cv, rotation, translation, mask);

  Eigen::Matrix3d rotation_matrix;

  cv::cv2eigen(rotation, rotation_matrix);

  Eigen::Vector3d euler = rotation_matrix.canonicalEulerAngles(2, 1, 0);

  accum1 += euler[0];
  accum2 += euler[1];
  accum3 += euler[2];

  std::println("Eulerian deltas: ({}, {}, {})", euler[0], euler[1], euler[2]);
  std::println("Eulerian accum: ({}, {}, {})", accum1, accum2, accum3);
}
