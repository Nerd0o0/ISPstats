#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <string>
#include "../unities/include/Base.h"
#include "../unities/include/JobsForPerson.h"
#include "../unities/include/JobsForSprint.h"
#include "../unities/include/LeaderPerson.h"
#include "../unities/include/SprintsAndProjects.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../include/DBConnector.h"

using nlohmann::json;
DBConnector connector;
TEST_CASE("getSprintsAndProjects") {
    CHECK(connector.getSprintsAndProjects().size() > 0);
}
TEST_CASE("getJobsForSprint") {
    CHECK(connector.getJobsForSprint(1).size() > 0);
}
TEST_CASE("getJobsForPerson") {
    CHECK(connector.getJobsForPerson(1).size() > 0);
}
TEST_CASE("getProjects") {
    CHECK(connector.getProjects().size() > 0);
}
TEST_CASE("getProjectForSprint") {
    auto project = connector.getProjectForSprint(1);
    CHECK(project.size()==1);
}
TEST_CASE("getPersons") {
    CHECK(connector.getPersons().size() > 0);
}
TEST_CASE("getSprintsForProject") {
    CHECK(connector.getSprintsForProject(1).size() > 0);
}
TEST_CASE("getMinRatioPersons") {
    auto leaders = connector.getMinRatioPersons();
    CHECK(leaders.size() <= 5);
}