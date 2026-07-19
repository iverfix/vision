#include "ConstantVelocity.h"
#include <Eigen/Dense>


ConstantVelocityModel::ConstantVelocityModel() : whiteNoise{ Eigen::Vector3d(sigmaForward, sigmaRight, sigmaDown).asDiagonal() } {}

CVState ConstantVelocityModel::transfer(const CVState &stateVector, std::chrono::duration<double> timestep) { return transitionMatrix(timestep) * stateVector; }


CVStateMatrix ConstantVelocityModel::transitionMatrix(std::chrono::duration<double> timestep)
{
  CVStateMatrix transferMatrix = CVStateMatrix::Identity();
  transferMatrix.block<3, 3>(0, 3) = Eigen::Matrix3d::Identity() * timestep.count();

  return transferMatrix;
}

CVStateMatrix ConstantVelocityModel::processNoise(std::chrono::duration<double> timestep) const
{
  CVStateMatrix processNoise;
  const double deltaT = timestep.count();

  const Eigen::Matrix3d offDiagonal = 0.5 * whiteNoise * deltaT * deltaT;

  processNoise.block<3, 3>(0, 0) = (1.0 / 3.0) * whiteNoise * deltaT * deltaT * deltaT;
  processNoise.block<3, 3>(3, 3) = whiteNoise * deltaT;
  processNoise.block<3, 3>(0, 3) = offDiagonal;
  processNoise.block<3, 3>(3, 0) = offDiagonal;

  return processNoise;
}
