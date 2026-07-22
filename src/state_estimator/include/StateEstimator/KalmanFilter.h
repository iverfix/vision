#pragma once
#include "Models/ConstantVelocity.h"
#include <Eigen/Dense>
#include <NavigationTypes/Types.h>

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
  KalmanFilter(StateVector priorState, StateMatrix priorCovariance, TimestampType startTime);
  [[nodiscard]] StateVector predict(TimestampType predictionTime);
  void update(MeasurementMatrix measurementMatrix, MeasurementCovariance measurementNoise, MeasurementVector measurement, TimestampType time);


private:
  void computeKalmanGain();
  [[nodiscard]] KalmanGainMatrix computeKalmanGain(MeasurementMatrix measurementMatrix, MeasurementCovariance measurementNoise) const;
  StateVector priorState;
  StateMatrix priorCovariance;
  StateVector posterioriState;
  StateMatrix posterioriCovariance;
  ConstantVelocityModel model;
  TimestampType lastUpdate;
};
