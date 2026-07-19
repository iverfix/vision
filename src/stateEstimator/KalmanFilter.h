#pragma once
#include "ConstantVelocity.h"
#include <Eigen/Dense>
#include <chrono>


// TODO: Utilize templates for this class

static constexpr int MEASUREMENT_SIZE = 3;

using StateMatrix = Eigen::Matrix<double, STATE_SIZE, STATE_SIZE, Eigen::RowMajor>;
using StateVector = Eigen::Vector<double, STATE_SIZE>;
using MeasurementVector = Eigen::Vector<double, MEASUREMENT_SIZE>;
using MeasurementMatrix = Eigen::Matrix<double, MEASUREMENT_SIZE, STATE_SIZE>;
using KalmanGainMatrix = Eigen::Matrix<double, STATE_SIZE, MEASUREMENT_SIZE>;
using MeasurementCovariance = Eigen::Matrix<double, MEASUREMENT_SIZE, MEASUREMENT_SIZE>;


class KalmanFilter
{

public:
  KalmanFilter(StateVector priorState, StateMatrix priorCovariance, std::chrono::steady_clock::time_point startTime);
  void predict();
  void update(MeasurementMatrix measurementMatrix, MeasurementCovariance measurementNoise, MeasurementVector measurement);

private:
  void computeKalmanGain();
  KalmanGainMatrix computeKalmanGain(MeasurementMatrix measurementMatrix, MeasurementCovariance measurementNoise);

  StateVector priorState;
  StateMatrix priorCovariance;
  StateVector posterioriState;
  StateMatrix posterioriCovariance;
  ConstantVelocityModel model;
  std::chrono::steady_clock::time_point lastUpdate;
};
