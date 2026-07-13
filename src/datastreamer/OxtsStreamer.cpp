#include "OxtsStreamer.h"
#include "StreamerUtil.h"


OxtsStreamer::OxtsStreamer(std::filesystem::path path)
  : datasetRootDirectory(std::move(path)), files(fetchDataPages(datasetRootDirectory))
{}
