#include "DataStreamer/OxtsStreamer.h"
#include "DataStreamer/DataTypes.h"
#include "StreamerUtil.h"
#include <fstream>
#include <optional>
#include <string>

constexpr size_t Latitude = 0;
constexpr size_t Longitude = 1;
constexpr size_t Altitude = 2;
constexpr size_t Roll = 3;
constexpr size_t Pitch = 4;
constexpr size_t Yaw = 5;
constexpr size_t VelocityNorth = 6;
constexpr size_t VelocityEast = 7;
constexpr size_t VelocityForward = 8;
constexpr size_t VelocityLeft = 9;
constexpr size_t VelocityUp = 10;
constexpr size_t AccelerationIMUX = 11;
constexpr size_t AccelerationIMUY = 12;
constexpr size_t AccelerationIMUZ = 13;
constexpr size_t AccelerationForward = 14;
constexpr size_t AccelerationLeft = 15;
constexpr size_t AccelerationUP = 16;
constexpr size_t AngularVelocityIMUX = 17;
constexpr size_t AngularVelocityIMUY = 18;
constexpr size_t AngularVelocityIMUZ = 19;
constexpr size_t AngularVelocityForward = 20;
constexpr size_t AngularVelocityLeft = 21;
constexpr size_t AngularVelocityUP = 22;
constexpr size_t PositionAccuracy = 23;
constexpr size_t VelocityAccuracy = 24;
constexpr size_t Navstate = 25;
constexpr size_t NumSats = 26;
constexpr size_t PosMode = 27;
constexpr size_t VelMode = 27;
constexpr size_t OriMode = 29;

constexpr size_t NUM_MEASUREMENTS = 30;

OxtsStreamer::OxtsStreamer(std::filesystem::path path) : datasetRootDirectory(std::move(path)), files(fetchDataPages(datasetRootDirectory)) {}


std::optional<OxtsData> OxtsStreamer::fetchNextMeasurement()
{

  if (nextImageIndex >= files.size()) { return std::nullopt; };
  const auto &currentFile = files[nextImageIndex++];
  const std::optional<OxtsMeasurement> currentDocument = parseOxtsFile(datasetRootDirectory / "data" / currentFile.path);

  if (currentDocument == std::nullopt) { return std::nullopt; };

  return OxtsData{ .measurement = currentDocument.value(), .time = currentFile.timestamp };
}

std::optional<OxtsMeasurement> OxtsStreamer::parseOxtsFile(const std::filesystem::path &path)
{
  std::ifstream file{ path };

  std::vector<double> measurements{};

  for (std::string line; std::getline(file, line);) {

    std::stringstream stream{ line };

    for (double measurement{}; stream >> measurement;) {
      measurements.push_back(measurement);
    }
  }

  if (measurements.size() != NUM_MEASUREMENTS) { return std::nullopt; }

  GeodeticPosition geoPosition{ .latitude = measurements[Latitude], .longitude = measurements[Longitude], .altitude = measurements[Altitude] };
  Orientation orientation{ measurements[Roll], measurements[Pitch], measurements[Yaw] };
  NorthEastVelocity northEastVelocity{ measurements[VelocityNorth], measurements[VelocityEast] };
  LinearVelocity linearVelocity{ measurements[VelocityForward], measurements[VelocityLeft], measurements[VelocityUp] };
  LinearAcceleration linearAccelerationIMUFrame{ measurements[AccelerationIMUX], measurements[AccelerationIMUY], measurements[AccelerationIMUZ] };
  LinearAcceleration linearAccelerationBodyFrame{ measurements[AccelerationForward], measurements[AccelerationLeft], measurements[AccelerationUP] };
  AngularVelocity angularVelocityIMUFrame{ measurements[AngularVelocityIMUX], measurements[AngularVelocityIMUY], measurements[AngularVelocityIMUZ] };
  AngularVelocity angularVelocityBodyFrame{ measurements[AngularVelocityForward], measurements[AngularVelocityLeft], measurements[AngularVelocityUP] };
  GPSAccuracy gpsAccuracy{ measurements[PositionAccuracy], measurements[VelocityAccuracy] };
  GPSMetadata gpsMetadata{ .navstat = static_cast<int>(measurements[Navstate]),
    .numsats = static_cast<int>(measurements[NumSats]),
    .posmode = static_cast<int>(measurements[PosMode]),
    .velmode = static_cast<int>(measurements[VelMode]),
    .orimode = static_cast<int>(measurements[OriMode]) };

  return OxtsMeasurement{ .geodeticPostion = geoPosition,
    .orientation = convertFromUSToEUOrientation(orientation),
    .velocityNorthEast = northEastVelocity,
    .velocityBody = convertFromUSToEUOrientation(linearVelocity),
    .accelerationIMU = convertFromUSToEUOrientation(linearAccelerationIMUFrame),
    .accelerationBody = convertFromUSToEUOrientation(linearAccelerationBodyFrame),
    .angularVelocityIMU = convertFromUSToEUOrientation(angularVelocityIMUFrame),
    .angularVelocityBody = convertFromUSToEUOrientation(angularVelocityBodyFrame),
    .gpsAccuracy = gpsAccuracy,
    .gpsMetadata = gpsMetadata };
}
