#include "KalmanFilter.h"
#include <Eigen/Core>


KalmanFilter::KalmanFilter(StateVector priorState, StateMatrix priorCovariance)
  : priorState(std::move(priorState)), priorCovariance(std::move(priorCovariance)), estimatedState(StateVector::Zero()), esimateCovariance(StateMatrix::Zero())
{}

void KalmanFilter::predict() {}

void KalmanFilter::update(MeasurementMatrix measurementFunction,
  Eigen::Matrix<double, MEASUREMENT_SIZE, MEASUREMENT_SIZE> measurementNoise,
  MeasurementVector measurement)

{
  KalmanGainMatrix kalmanGain = computeKalmanGain(measurementFunction, measurementNoise);
  estimatedState = priorState + kalmanGain * (measurement - measurementFunction * priorState);
  esimateCovariance = (StateMatrix::Identity() - kalmanGain * measurementFunction) * priorCovariance;
}

KalmanGainMatrix KalmanFilter::computeKalmanGain(MeasurementMatrix measurementFunction,
  Eigen::Matrix<double, MEASUREMENT_SIZE, MEASUREMENT_SIZE> measurementNoise)
{
  return priorCovariance * measurementFunction.transpose()
         * (measurementFunction * priorCovariance * measurementFunction.transpose() + measurementNoise).inverse();
}
