#pragma once

#include <Poco/Mutex.h>
#include <Poco/Util/ServerApplication.h>


class Server : public Poco::Util::ServerApplication
{
protected:
	int main(const std::vector<std::string> &);
	static Poco::Mutex textLock;
};