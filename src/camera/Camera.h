#pragma once
#include <Eigen/Dense>
#include <filesystem>

static constexpr size_t nDistParams = 5;

class Camera
{

public:
  Camera(int camera_id, const std::filesystem::path &path);
  [[nodiscard]] Eigen::Matrix<double, 3, 3, Eigen::RowMajor> getCameraMatrix() const { return cameraMatrix; }


private:
  void parseCalibrationFile(const std::filesystem::path &path);

  int camera_id{};
  Eigen::Vector2d aspect_ratio{};
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> cameraMatrix{};
  Eigen::Vector<double, nDistParams> distorition_parameters{};
  Eigen::Matrix3d rotationMatrix{};
  Eigen::Vector3d translationVector{};
};
