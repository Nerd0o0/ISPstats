#include <Poco/Util/ServerApplication.h>


class Server : public Poco::Util::ServerApplication
{
protected:
	int main(const std::vector<std::string> &);
};