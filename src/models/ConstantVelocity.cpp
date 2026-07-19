#include "ConstantVelocity.h"
#include <Eigen/Dense>


ConstantVelocityModel::ConstantVelocityModel() : whiteNoise{ Eigen::Vector3d(sigmaForward, sigmaRight, sigmaDown).asDiagonal() } {}

CVState ConstantVelocityModel::transfer(const CVState &stateVector, double timestep) { return transitionMatrix(timestep) * stateVector; }


Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> ConstantVelocityModel::transitionMatrix(double timestep)
{
  Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> transferMatrix = Eigen::Matrix<double, STATE_SIZE, STATE_SIZE>::Identity();
  transferMatrix.block<3, 3>(0, 3) = timestep * Eigen::Matrix3d::Identity();

  return transferMatrix;
}


Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> ConstantVelocityModel::processNoise(double timestep) const
{
  Eigen::Matrix<double, STATE_SIZE, STATE_SIZE> processNoise;

  const Eigen::Matrix3d offDiagonal = (1 / 2) * whiteNoise * timestep * timestep;

  processNoise.block<3, 3>(0, 0) = (1 / 3) * whiteNoise * timestep * timestep * timestep;
  processNoise.block<3, 3>(3, 3) = whiteNoise * timestep;
  processNoise.block<3, 3>(0, 3) = offDiagonal;
  processNoise.block<3, 3>(3, 0) = offDiagonal;

  return processNoise;
}
