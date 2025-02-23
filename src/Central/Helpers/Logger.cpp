#include "Helpers/Logger.hpp"

#include <glog/logging.h>
#include "Helpers/Helpers.hpp"

namespace Central::Logger
{
    void InitializeLogger(Helpers::Logger _logger)
    {
        std::string _log = _logger.logPath + "/DccCentral";
        std::cout << "Logger Path " << _log << "\n";
        google::SetLogDestination((google::LogSeverity)_logger.level, _log.c_str());
        google::SetLogFilenameExtension(".log");
        google::InitGoogleLogging("DCCCentral");
    }
}
