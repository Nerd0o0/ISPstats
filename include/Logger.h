#pragma once

#include <Poco/AutoPtr.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Logger.h>
#include <Poco/PatternFormatter.h>

namespace Logger {
    Poco::Logger &InitLogger();
    Poco::Logger &GetLogger();
}
