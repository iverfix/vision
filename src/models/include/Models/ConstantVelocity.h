#pragma once
#include <Eigen/Dense>
#include <chrono>

static constexpr int STATE_SIZE = 6;

using CVState = Eigen::Vector<double, STATE_SIZE>;
using CVStateMatrix = Eigen::Matrix<double, STATE_SIZE, STATE_SIZE>;

class ConstantVelocityModel
{
public:
  ConstantVelocityModel();
  [[nodiscard]] static CVStateMatrix transitionMatrix(std::chrono::duration<double> timestep);
  [[nodiscard]] static CVState transfer(const CVState &stateVector, std::chrono::duration<double> timestep);
  [[nodiscard]] CVStateMatrix processNoise(std::chrono::duration<double> timestep) const;

private:
  double sigmaForward{ 6.0 };
  double sigmaRight{ 0.5 };
  double sigmaDown{ 0.1 };
  Eigen::Matrix3d whiteNoise;
};
