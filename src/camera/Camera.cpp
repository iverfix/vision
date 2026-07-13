#include "Camera.h"
#include <fstream>
#include <string>
#include <vector>

static constexpr int aspectRatioVectorSize = 2;
static constexpr int cameraMatrixSize = 9;
static constexpr int rotationMatrixSize = 9;
static constexpr int distortionParametersListSize = 5;
static constexpr int translationVectorSize = 3;

namespace {

template<typename EigenType> EigenType parseEigen(std::stringstream &stream, int numParameters, const std::string &error_message)
{
  std::vector<double> output{};
  double element{};
  while (stream >> element) { output.push_back(element); }

  if (output.size() != numParameters) { throw std::runtime_error(error_message); }

  return Eigen::Map<EigenType>(output.data());
}

};// namespace

Camera::Camera(int camera_id, const std::filesystem::path &path) : camera_id(camera_id) { parseCalibrationFile(path); }

void Camera::parseCalibrationFile(const std::filesystem::path &path)
{
  std::ifstream cameraCalibrationFile{ path / "calibration" / "calib_cam_to_cam.txt" };

  std::string line;
  while (std::getline(cameraCalibrationFile, line)) {
    std::stringstream stream(line);
    std::string field;
    stream >> field;
    if (field.starts_with(std::format("S_0{}", camera_id))) {
      aspect_ratio = parseEigen<Eigen::Vector2d>(stream, aspectRatioVectorSize, "Invalid aspect ratio");

    } else if (field.starts_with(std::format("K_0{}", camera_id))) {
      cameraMatrix = parseEigen<Eigen::Matrix<double, 3, 3, Eigen::RowMajor>>(stream, cameraMatrixSize, "Invalid camera matrix");

    } else if (field.starts_with(std::format("D_0{}", camera_id))) {
      distorition_parameters = parseEigen<Eigen::Vector<double, nDistParams>>(stream, distortionParametersListSize, "Invalid distortion parameters list");

    } else if (field.starts_with(std::format("R_0{}", camera_id))) {
      rotationMatrix = parseEigen<Eigen::Matrix3d>(stream, rotationMatrixSize, "Invalid rotation matrix");

    } else if (field.starts_with(std::format("T_0{}", camera_id))) {
      translationVector = parseEigen<Eigen::Vector3d>(stream, translationVectorSize, "Invalid translation vector");
    }
  }
}
