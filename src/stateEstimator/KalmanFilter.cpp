#include "KalmanFilter.h"
#include <Eigen/Core>
#include <chrono>


KalmanFilter::KalmanFilter(StateVector priorState, StateMatrix priorCovariance, std::chrono::steady_clock::time_point startTime)
  : priorState(std::move(priorState)), priorCovariance(std::move(priorCovariance)), posterioriState(StateVector::Zero()),
    posterioriCovariance(StateMatrix::Zero()), lastUpdate(startTime)
{}

void KalmanFilter::predict()
{
  const auto timestep = std::chrono::steady_clock::now() - lastUpdate;
  const StateMatrix transitionMatrix = model.transitionMatrix(timestep);
  const StateMatrix processNoise = model.processNoise(timestep);
  priorState = transitionMatrix * posterioriState;
  priorCovariance = transitionMatrix * posterioriCovariance * transitionMatrix + processNoise;
}

void KalmanFilter::update(MeasurementMatrix measurementMatrix, MeasurementCovariance measurementNoise, MeasurementVector measurement)
{
  const KalmanGainMatrix kalmanGain = computeKalmanGain(measurementMatrix, measurementNoise);
  posterioriState = priorState + kalmanGain * (measurement - measurementMatrix * priorState);
  posterioriCovariance = (StateMatrix::Identity() - kalmanGain * measurementMatrix) * priorCovariance;
  lastUpdate = std::chrono::steady_clock::now();
}

KalmanGainMatrix KalmanFilter::computeKalmanGain(MeasurementMatrix measurementMatrix, MeasurementCovariance measurementNoise)
{ return priorCovariance * measurementMatrix.transpose() * (measurementMatrix * priorCovariance * measurementMatrix.transpose() + measurementNoise).inverse(); }
