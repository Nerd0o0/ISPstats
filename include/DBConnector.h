#pragma once
#include "../unities/include/SprintsAndProjects.h"
#include "../unities/include/JobsForSprint.h"
#include "../unities/include/JobsForPerson.h"
#include "../unities/include/SprintBase.h"
#include "../unities/include/ProjectBase.h"
#include "../unities/include/PersonBase.h"
#include "mysql.h"

using namespace std;
class DBConnector {
public:
    DBConnector();
    ~DBConnector();

    vector<unities::SprintsAndProjects> getSprintsAndProjects();
    vector<unities::JobsForSprint> getJobsForSprint(int);
    vector<unities::JobsForPerson> getJobsForPerson(int);
    vector<unities::SprintBase> getSprints();
    vector<unities::ProjectBase> getProjects();
    vector<unities::ProjectBase> getProjectForSprint(int);
    vector<unities::PersonBase> getPersons();
    vector<unities::SprintBase> getSprintsForProject(int);
    unities::PersonBase getMinRatioPerson();

private:
    MYSQL *connector;
    MYSQL_RES *res;
    MYSQL_ROW row;
};
