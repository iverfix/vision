#pragma once
#include <Eigen/Dense>

static constexpr int STATE_SIZE = 6;

using CVState = Eigen::Vector<double, STATE_SIZE>;

class ConstantVelocityModel
{
public:
  ConstantVelocityModel();
  // TODO: Use chrono for timesteps
  [[nodiscard]] static Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> transitionMatrix(double timestep);
  [[nodiscard]] static CVState transfer(const CVState &stateVector, double timestep);
  [[nodiscard]] Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> processNoise(double timestep) const;

private:
  Eigen::Matrix3d whiteNoise;
  double sigmaForward{ 6.0 };
  double sigmaRight{ 0.5 };
  double sigmaDown{};
};
