#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <chrono>
#include <filesystem>
#include <opencv2/core/mat.hpp>

using TimestampType = std::chrono::sys_time<std::chrono::nanoseconds>;

struct ImageData
{
  cv::Mat image;
  TimestampType time;
};


struct DataPage
{
  std::filesystem::path path;
  TimestampType timestamp;
};


// Coordinate frames
struct GeodeticPosition
{
  double latitude{};
  double longitude{};
  double altitude{};
};

using NorthEast = Eigen::Vector2d;
using Orientation = Eigen::Vector3d;

// Velocity

using LinearVelocity = Eigen::Vector3d;
using AngularVelocity = Eigen::Vector3d;
using NorthEastVelocity = Eigen::Vector2d;


// Acceleration
using LinearAcceleration = Eigen::Vector3d;

// GPS
using GPSAccuracy = Eigen::Vector2d;

struct GPSMetadata
{
  int navstat{};
  int numsats{};
  int posmode{};
  int velmode{};
  int orimode{};
};

struct OxtsMeasurement
{
  GeodeticPosition geodeticPostion{};
  Orientation orientation;
  NorthEastVelocity velocityNorthEast;
  LinearVelocity velocityBody;
  LinearAcceleration accelerationIMU;
  LinearAcceleration accelerationBody;
  AngularVelocity angularVelocityIMU;
  AngularVelocity angularVelocityBody;
  GPSAccuracy gpsAccuracy;
  GPSMetadata gpsMetadata;
};


struct OxtsData
{
  OxtsMeasurement measurement{};
  TimestampType time;
};
