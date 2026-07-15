#pragma once
#include "DataTypes.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <filesystem>
#include <type_traits>
#include <vector>

template<typename T>
concept LinalgType = std::same_as<std::remove_cvref_t<T>, Eigen::Matrix3d> || std::same_as<std::remove_cvref_t<T>, Eigen::Vector3d>;


template<LinalgType T> T convertFromUSToEUOrientation(const T &americanOrientedMatrix)
{
  static const Eigen::Matrix3d conversion = (Eigen::Matrix3d() << 1, 0, 0, 0, -1, 0, 0, 0, -1).finished();
  return conversion * americanOrientedMatrix;
}


std::vector<DataPage> fetchDataPages(const std::filesystem::path &datasetRootDirectory);
