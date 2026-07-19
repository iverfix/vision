#pragma once
#include "ConstantVelocity.h"
#include <Eigen/Dense>


// TODO: Utilize templates for this class

static constexpr int MEASUREMENT_SIZE = 3;

using StateMatrix = Eigen::Matrix<double, STATE_SIZE, STATE_SIZE, Eigen::RowMajor>;
using StateVector = Eigen::Vector<double, STATE_SIZE>;
using MeasurementVector = Eigen::Vector<double, MEASUREMENT_SIZE>;
using MeasurementMatrix = Eigen::Matrix<double, MEASUREMENT_SIZE, STATE_SIZE>;
using KalmanGainMatrix = Eigen::Matrix<double, STATE_SIZE, MEASUREMENT_SIZE>;


class KalmanFilter
{

public:
  KalmanFilter(StateVector priorState, StateMatrix priorCovariance);
  void predict();
  void update(MeasurementMatrix measurementFunction, Eigen::Matrix<double, MEASUREMENT_SIZE, MEASUREMENT_SIZE> measurementNoise, MeasurementVector measurement);

private:
  void computeKalmanGain();
  KalmanGainMatrix computeKalmanGain(MeasurementMatrix measurementFunction, Eigen::Matrix<double, MEASUREMENT_SIZE, MEASUREMENT_SIZE> measurementNoise);

  StateVector priorState;
  StateMatrix priorCovariance;
  StateVector estimatedState;
  StateMatrix esimateCovariance;
};
