#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include "../src/DBConnector.cpp"

class RestHandler : public Poco::Net::HTTPRequestHandler {
    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override {
        response.setContentType("application/json");
        try {
            HandleRestRequest(request, response);
        } catch (const std::exception &e) {
            nlohmann::json result;
            result["error"] = e.what();
            response.send() << result;
        }
    }
    virtual void HandleRestRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) = 0;
};

class getProjects:public RestHandler{
    void HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};

class getSprints:public RestHandler{
    void HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};
class getPersons:public RestHandler{
    void HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};
class getSprintsForProject:public RestHandler{
    int project_id;
    void HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
public: getSprintsForProject(int id):project_id(id){}
};
class getSprintsAndProjects:public RestHandler{
    void HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};
class getJobsForSprint:public RestHandler{
    int sprint_id;
    void HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
public: getJobsForSprint(int id):sprint_id(id){}
};
class getJobsForPerson:public RestHandler{
    int person_id;
    void HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
public: getJobsForPerson(int id):person_id(id){}
};