#include "../include/Logger.h"

Poco::Logger &Logger::InitLogger() {
    //Poco::AutoPtr<Poco::ConsoleChannel> console(new Poco::ConsoleChannel);

    Poco::AutoPtr<Poco::SimpleFileChannel> file(new Poco::SimpleFileChannel("/home/nerd/CLionProjects/ISPstats/log.log"));
    file->open();
    Poco::AutoPtr<Poco::PatternFormatter> formatter(new Poco::PatternFormatter);
    formatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
    Poco::AutoPtr<Poco::FormattingChannel> channel(new Poco::FormattingChannel(formatter, file));
    Poco::Logger::root().setChannel(channel);
    Poco::Logger::root().setLevel("trace");
    return Poco::Logger::get("Logger");
}
Poco::Logger &Logger::GetLogger() {
    static Poco::Logger &logger{InitLogger()};
    return logger;
}