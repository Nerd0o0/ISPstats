#pragma once
#include "../unities/include/SprintsAndProjects.h"
#include "../unities/include/JobsForSprint.h"
#include "../unities/include/JobsForPerson.h"
#include "../unities/include/Base.h"
#include "../unities/include/LeaderPerson.h"
#include "mysql.h"

using namespace std;
class DBConnector {
public:
    DBConnector();
    DBConnector(string user, string password);
    ~DBConnector();

    vector<unities::SprintsAndProjects> getSprintsAndProjects();
    vector<unities::JobsForSprint> getJobsForSprint(int);
    vector<unities::JobsForPerson> getJobsForPerson(int);
    vector<unities::Base> getProjects();
    vector<unities::Base> getProjectForSprint(int);
    vector<unities::Base> getPersons();
    vector<unities::Base> getSprintsForProject(int);
    vector<unities::LeaderPerson> getMinRatioPersons();
    int initDatabase();
    int loadData(std::istream&);

private:
    MYSQL *connector;
    MYSQL_RES *res;
    MYSQL_ROW row;
};
