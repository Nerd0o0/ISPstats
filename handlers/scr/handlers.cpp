#include "../include/handlers.h"
#include "../../include/DBConnector.h"

void getProjects::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
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
    auto persons=connector.getPersons();
    for(auto person:persons){
        result.push_back(person);
    }
    response.send() << result;
}
void getProjectForSprint::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    auto persons=connector.getProjectForSprint(sprint_id);
    for(auto person:persons){
        result.push_back(person);
    }
    response.send() << result;
}
void getSprintsForProject::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    auto sprints=connector.getSprintsForProject(getSprintsForProject::project_id);
    for(auto sprint:sprints){
        result.push_back(sprint);
    }
    response.send() << result;
}
void getSprintsAndProjects::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response){
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    auto sprints=connector.getSprintsAndProjects();
    for(auto sprint:sprints){
        result.push_back(sprint);
    }
    response.send()<<result;
}
void getJobsForSprint::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    auto jobs=connector.getJobsForSprint(getJobsForSprint::sprint_id);
    for(auto job:jobs){
        result.push_back(job);
    }
    response.send() << result;
}
void getJobsForPerson::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    auto jobs=connector.getJobsForPerson(getJobsForPerson::person_id);
    for(auto job:jobs){
        result.push_back(job);
    }
    response.send() << result;
}
void getLeadersList::HandleRestRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.add("Access-Control-Allow-Origin","*");
    response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
    nlohmann::json result = nlohmann::json::array();
    DBConnector connector;
    auto person=connector.getMinRatioPerson();
    result.push_back(person);
    response.send() << result;
}