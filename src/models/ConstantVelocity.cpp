#include "ConstantVelocity.h"
#include <Eigen/Dense>


CVState ConstantVelocityModel::transfer(const CVState &stateVector, double timestep) { return transitionMatrix(timestep) * stateVector; }


Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> ConstantVelocityModel::transitionMatrix(double timestep)
{
  Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> transferMatrix = Eigen::Matrix<double, STATE_SIZE, STATE_SIZE>::Identity();
  transferMatrix.block<3, 3>(0, 3) = timestep * Eigen::Matrix3d::Identity();

  return transferMatrix;
}


Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> ConstantVelocityModel::processNoise(double timestep)
{
  // TODO: Implement this
  return timestep * Eigen::Matrix<double, STATE_SIZE, STATE_SIZE>::Identity();
}
