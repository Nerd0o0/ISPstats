#include "../include/Factory.h"
#include "../include/Error.h"
#include "../include/handlers.h"
#include <iostream>
#include <Poco/Net/HTTPServerRequest.h>
#include <regex>
//#define DEBUG

namespace handlers {
    HTTPRequestHandler *Factory::GetMethodHandlers(const std::string &uri) const {
        if (uri == "/" || uri == "/getProjects") {
#ifdef DEBUG
            std::cout<<"geProjects"<<std::endl;
#endif
            return new getProjects();
        } else if (uri == "/getSprints") {
#ifdef DEBUG
            std::cout<<"getSprints"<<std::endl;
#endif
            return new getSprints();
        } else if (uri == "/getPersons") {
#ifdef DEBUG
            std::cout<<"getPersons"<<std::endl;
#endif
            return new getPersons();
        }else if (std::smatch m; std::regex_match(uri, m, std::regex{R"(/getProjectForSprint/(\d+))"})) {
#ifdef DEBUG
            std::cout<<"getProjectForSprint"<<m[1]<<std::endl;
#endif
            return new getProjectForSprint(std::stoi(m[1]));
        } else if (std::smatch m; std::regex_match(uri, m, std::regex{R"(/getSprintsForProject/(\d+))"})) {
#ifdef DEBUG
            std::cout<<"getSprintsForProjects"<<m[1]<<std::endl;
#endif
            return new getSprintsForProject(std::stoi(m[1]));
        } else if (uri == "/getSprintsAndProjects") {
#ifdef DEBUG
            std::cout<<"getSprintsAndProjects"<<std::endl;
#endif
            return new getSprintsAndProjects;
        } else if (std::smatch m; std::regex_match(uri, m, std::regex{R"(/getJobsForSprint/(\d+))"})) {
#ifdef DEBUG
            std::cout<<"getJobsForSprint"<<m[1]<<std::endl;
#endif
            return new getJobsForSprint(std::stoi(m[1]));
        } else if (std::smatch m; std::regex_match(uri, m, std::regex{R"(/getJobsForPerson/(\d+))"})) {
#ifdef DEBUG
            std::cout<<"getJobsForPerson"<<m[1]<<std::endl;
#endif
            return new getJobsForPerson(std::stoi(m[1]));
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