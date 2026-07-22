#include "StateEstimator/KalmanFilter.h"
#include <Eigen/Core>
#include <chrono>


KalmanFilter::KalmanFilter(StateVector priorState, StateMatrix priorCovariance, TimestampType startTime)
  : priorState(std::move(priorState)), priorCovariance(std::move(priorCovariance)), posterioriState(StateVector::Zero()),
    posterioriCovariance(StateMatrix::Zero()), lastUpdate(startTime)
{}

StateVector KalmanFilter::predict(TimestampType predictionTime)
{
  const auto timestep = predictionTime - lastUpdate;
  const StateMatrix transitionMatrix = model.transitionMatrix(timestep);
  const StateMatrix processNoise = model.processNoise(timestep);
  priorState = transitionMatrix * posterioriState;
  priorCovariance = transitionMatrix * posterioriCovariance * transitionMatrix + processNoise;
  return priorState;
}

void KalmanFilter::update(MeasurementMatrix measurementMatrix, MeasurementCovariance measurementNoise, MeasurementVector measurement, TimestampType time)
{
  const KalmanGainMatrix kalmanGain = computeKalmanGain(measurementMatrix, measurementNoise);
  posterioriState = priorState + kalmanGain * (measurement - measurementMatrix * priorState);
  posterioriCovariance = (StateMatrix::Identity() - kalmanGain * measurementMatrix) * priorCovariance;
  lastUpdate = time;
}

KalmanGainMatrix KalmanFilter::computeKalmanGain(MeasurementMatrix measurementMatrix, MeasurementCovariance measurementNoise) const
{ return priorCovariance * measurementMatrix.transpose() * (measurementMatrix * priorCovariance * measurementMatrix.transpose() + measurementNoise).inverse(); }
