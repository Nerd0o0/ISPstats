#include "../include/Factory.h"
#include "../include/Error.h"
#include "../include/handlers.h"
#include <iostream>
#include <Poco/Net/HTTPServerRequest.h>
#include <regex>
#include "../../include/Logger.h"

namespace handlers {
    HTTPRequestHandler *Factory::GetMethodHandlers(const std::string &uri) const {
        if (uri == "/" || uri == "/getProjects") {
            Logger::GetLogger().information("/getProjects");
            return new getProjects();
        } else if (uri == "/getSprints") {
            Logger::GetLogger().information("/getSprints");
            return new getSprints();
        } else if (uri == "/getPersons") {
            Logger::GetLogger().information("/getPersons");
            return new getPersons();
        }else if (std::smatch m; std::regex_match(uri, m, std::regex{R"(/getProjectForSprint/(\d+))"})) {
            Logger::GetLogger().information("/getProjectForSprint" + m[1].str());
            return new getProjectForSprint(std::stoi(m[1]));
        } else if (std::smatch m; std::regex_match(uri, m, std::regex{R"(/getSprintsForProject/(\d+))"})) {
            Logger::GetLogger().information("getSprintsForProjects" + m[1].str());
            return new getSprintsForProject(std::stoi(m[1]));
        } else if (uri == "/getSprintsAndProjects") {
            Logger::GetLogger().information("/getSprintsAndProjects");
            return new getSprintsAndProjects;
        } else if (std::smatch m; std::regex_match(uri, m, std::regex{R"(/getJobsForSprint/(\d+))"})) {
            Logger::GetLogger().information("getJobsForSprint"+m[1].str());
            return new getJobsForSprint(std::stoi(m[1]));
        } else if (std::smatch m; std::regex_match(uri, m, std::regex{R"(/getJobsForPerson/(\d+))"})) {
            Logger::GetLogger().information("getJobsForPerson"+m[1].str());
            return new getJobsForPerson(std::stoi(m[1]));
        } else if (uri == "/getLeadersList"){
            std::cout<<"getLeadersList"<<std::endl;
            Logger::GetLogger().information("getLeadersList");
            return new getLeadersList();
        }
        return nullptr;
    }
    HTTPRequestHandler *Factory::PostMethodHandlers(const std::string &uri) const {
        /*if (uri == "/" || uri=="/index" || uri=="/projects") {
            //return new UserMeetingList();
        }*/
        return nullptr;
    }
    Poco::Net::HTTPRequestHandler *Factory::createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
        using Poco::Net::HTTPRequest;

        Poco::Net::HTTPRequestHandler *result = nullptr;
        const auto &method = request.getMethod();
        const auto &uri = request.getURI();
        if (method == HTTPRequest::HTTP_GET) {
            result = GetMethodHandlers(uri);
        } else if (method == HTTPRequest::HTTP_POST) {
            result = PostMethodHandlers(uri);
        }

        if (result == nullptr) {
            return new Error(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST, "Wrong endpoint " + uri);
        }
        return result;
    }
}