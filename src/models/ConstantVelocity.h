#pragma once
#include <Eigen/Dense>

static constexpr int STATE_SIZE = 6;

using CVState = Eigen::Vector<double, STATE_SIZE>;

class ConstantVelocityModel
{
public:
  ConstantVelocityModel() = default;
  // TODO: Use chrono for timesteps
  static Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> transitionMatrix(double timestep);
  static CVState transfer(const CVState &stateVector, double timestep);
  static Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> processNoise(double timestep);
};
