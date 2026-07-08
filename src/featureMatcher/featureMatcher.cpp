#include "featureMatcher.h"
#include <Eigen/Dense>
#include <iostream>
#include <opencv2/core/eigen.hpp>
#include <print>
#include <vector>


FeatureMatcher::FeatureMatcher() { orbDetector = cv::ORB::create(); }

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
    dst_pts.push_back(kp2[match.trainIdx].pt);
  }

  cv::Mat H = cv::findHomography(src_pts, dst_pts, cv::RANSAC, 5.0);

  std::cout << H << std::endl;
}


void FeatureMatcher::getPoseDelta2(const cv::Mat &firstImage, const cv::Mat &secondImage, const Camera &camera)
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
    dst_pts.push_back(kp2[match.trainIdx].pt);
  }

  cv::Mat H = cv::findHomography(src_pts, dst_pts, cv::RANSAC, 5.0);


  std::vector<cv::Mat> rotations;
  std::vector<cv::Mat> translations;
  std::vector<cv::Mat> normals;
  cv::Mat k_cv;

  cv::eigen2cv(camera.getCameraMatrix(), k_cv);

  int num_solutions = cv::decomposeHomographyMat(H, k_cv, rotations, translations, normals);

  std::println("Number of solutions: {}", num_solutions);

  cv::Mat correct_R, correct_T;
  bool solution_found;

  for (int i = 0; i < num_solutions; ++i) {
    cv::Mat R = rotations[i];
    cv::Mat T = translations[i];
    cv::Mat normal = normals[i];

    if (T.at<double>(2) > 0) {
      correct_R = R;
      correct_T = T;
      solution_found = true;
      break;
    }
  }

  std::cout << "Rotation: " << correct_R << '\n';
  std::cout << "Translation: " << correct_T << '\n';

  Eigen::Matrix3d mat;

  cv::cv2eigen(correct_R, mat);

  Eigen::Vector3d euler = mat.canonicalEulerAngles(2, 1, 0);

  std::println("Eulerian deltas: ({}, {}, {})", euler[0], euler[1], euler[2]);
}
