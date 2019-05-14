#include "handlers.h"

void getProjects::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    std::cout<<"getProjects"<<std::endl;
    auto projects = connector.getProjects();
    for (auto project:projects) {
        result.push_back(project);
    }
    response.send() << result;
}
void getSprints::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    std::cout<<"getSprints"<<std::endl;
    auto sprints = connector.getSprints();
    for (auto sprint:sprints) {
        result.push_back(sprint);
    }
    response.send() << result;
}
void getPersons::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    std::cout<<"getPersons"<<std::endl;
    auto persons=connector.getPersons();
    for(auto person:persons){
        result.push_back(person);
    }
    response.send() << result;
}
void getSprintsForProject::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {}
void getSprintsAndProjects::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {}
void getJobsForSprint::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    auto persons=connector.getJobsForSprints(getJobsForSprint::sprint_id);
    std::cout<<"getJobsForSprint "<<getJobsForSprint::sprint_id<<std::endl;
    for(auto person:persons){
        result.push_back(person);
    }
    response.send() << result;
}
void getJobsForPerson::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {}