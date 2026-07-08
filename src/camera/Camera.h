#include <Eigen/Dense>
#include <filesystem>

static constexpr size_t nDistParams = 5;

class Camera
{

public:
  Camera(int camera_id, const std::filesystem::path &path);

private:
  void parseCalibrationFile(const std::filesystem::path &path);

  int camera_id{};
  Eigen::Vector2d aspect_ratio{};
  Eigen::Matrix3d cameraMatrix{};
  Eigen::Vector<double, nDistParams> distorition_parameters{};
  Eigen::Matrix3d rotationMatrix{};
  Eigen::Vector3d translationVector{};
};
