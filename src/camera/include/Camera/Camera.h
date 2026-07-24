#pragma once
#include <Eigen/Dense>
#include <filesystem>


class Camera
{

public:
  Camera(int camera_id, const std::filesystem::path &path);
  [[nodiscard]] Eigen::Matrix<double, 3, 3, Eigen::RowMajor> getCameraMatrix() const { return cameraMatrix; }

  static constexpr size_t aspectRatioVectorSize = 2;
  static constexpr size_t cameraMatrixSize = 9;
  static constexpr size_t rotationMatrixSize = 9;
  static constexpr size_t distortionParametersListSize = 5;
  static constexpr size_t translationVectorSize = 3;

private:
  void parseCalibrationFile(const std::filesystem::path &path);

  int camera_id{};
  Eigen::Vector2d aspect_ratio{};
  Eigen::Matrix<double, 3, 3, Eigen::RowMajor> cameraMatrix{};
  Eigen::Vector<double, distortionParametersListSize> distorition_parameters{};
  Eigen::Matrix3d rotationMatrix{};
  Eigen::Vector3d translationVector{};
};
