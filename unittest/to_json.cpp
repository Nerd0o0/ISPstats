#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <string>
#include <iostream>
#include "../unities/include/Base.h"
#include "../unities/include/JobsForPerson.h"
#include "../unities/include/JobsForSprint.h"
#include "../unities/include/LeaderPerson.h"
#include "../unities/include/SprintsAndProjects.h"
#include <boost/date_time/gregorian/gregorian.hpp>

using nlohmann::json;

TEST_CASE("json_marshal_Base") {
    unities::Base source(1, "name");

    json target = R"(
	{
		"id": 1,
		"name": "name"
	}
 )"_json;
    CHECK(json::diff(json(source),target).empty());
}
TEST_CASE("json_marshal_JobsForPerson") {
    std::string name = "name";
    unities::JobsForPerson source("projectName",1,"sprintName",1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);

    json target = R"(
	{
		"project": "projectName",
		"sprintID": 1,
        "sprint": "sprintName",
        "completeCount": 1,
        "completeEstTime": 1,
        "completeFactTime": 1,
        "incompleteCount": 1,
        "incompleteEstTime": 1,
        "incompleteFactTime": 1,
        "completeHelpTime": 1,
        "completeHelpCount": 1,
        "incompleteHelpTime": 1,
        "incompleteHelpCount": 1,
        "codeReturns": 1,
        "codeDiscussion": 1,
        "codeBranches": 1,
        "codeMerged": 1,
        "codeSeen": 1,
        "codeCommented": 1,
        "workTime": 1
	}
 )"_json;
    CHECK(json::diff(json(source),target).empty());
}
TEST_CASE("json_marshal_JobsForSprint") {
    unities::JobsForSprint source(1, "name",1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);

    json target = R"(
	{
		"personID": 1,
		"person": "name",
        "completeCount": 1,
        "completeEstTime": 1,
        "completeFactTime": 1,
        "incompleteCount": 1,
        "incompleteEstTime": 1,
        "incompleteFactTime": 1,
        "completeHelpTime": 1,
        "completeHelpCount": 1,
        "incompleteHelpTime": 1,
        "incompleteHelpCount": 1,
        "codeReturns": 1,
        "codeDiscussion": 1,
        "codeBranches": 1,
        "codeMerged": 1,
        "codeSeen": 1,
        "codeCommented": 1,
        "workTime": 1
	}
 )"_json;
    CHECK(json::diff(json(source),target).empty());
}
TEST_CASE("json_marshal_LeaderPerson") {
    unities::LeaderPerson source(1, "name", 0.5);

    json target = R"(
	{
		"personID": 1,
		"name": "name",
        "value": 0.5
	}
 )"_json;
    CHECK(json::diff(json(source),target).empty());
}
TEST_CASE("json_marshal_SprintsAndProjects") {
    unities::SprintsAndProjects source(1, "ProjectName","SprintName", "2019-06-06","2019-06-06", 1,1,1,1,1,1,1,1,1,1,1);
    //std::cout<<boost::gregorian::from_string("2019-06-06").day_number()-2440588;
    json target = R"(
	{
		"sprintID": 1,
		"project": "ProjectName",
        "sprint": "SprintName",
        "begin": 18053,
        "bugCount": 1,
        "estimationBugTime": 1,
        "completeBugCount": 1,
        "completeBugEstimation": 1,
        "completeBugFact": 1,
        "incompleteBugCount": 1,
        "incompleteBugEstimation": 1,
        "incompleteBugFact": 1,
        "codeBranches": 1,
        "codeDiscussion": 1,
        "codeReturns": 1
	}
 )"_json;
    CHECK(json::diff(json(source),target).empty());
}

