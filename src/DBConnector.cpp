#include "../include/DBConnector.h"
using namespace std;
DBConnector::DBConnector() {
    mysql_debug("d:t:O");
    try {
        connector = mysql_init(NULL);

    } catch (std::exception &e) {
        cout << "err" << endl;
        cout << e.what() << endl;
    }


    if (!mysql_real_connect(connector, "localhost", "stats", "q1w2e3r4",
                            "statsDB", 3306, NULL/*"/var/run/mysqld/mysqld.sock"*/, 0) &&
        mysql_set_character_set(connector, "utf8")) {
        printf("Error(%d) [%s] \"%s\"", mysql_errno(connector),
               mysql_sqlstate(connector),
               mysql_error(connector));
        mysql_close(connector);
        exit(-1);
    }
}

DBConnector::~DBConnector() {
    mysql_close(connector);
}

vector<unities::SprintsAndProjects> DBConnector::getSprintsAndProjects() {
    mysql_query(connector, "select SprintID Project.Name, Sprint.Name, BugCount, EstimationBugTime, CompleteBugCount,"
                           "CompleteBugEstimation, CompleteBugFact, IncompleteBugCount, IncompleteBugEstimation, IncompleteBugFact,"
                           "CodeReturns, CodeDiscussion from Sprint, Project where Sprint.ProjectID=Project.ProjectID;");
    vector<unities::SprintsAndProjects> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::SprintsAndProjects(row));
        }
        mysql_free_result(res);
    }
    return vector;
}

vector<unities::JobsForSprint> DBConnector::getJobsForSprint(int sprintID) {
    //s=std::strcat(*s," );
    std::string s = std::string(std::string("SELECT Person.PersonID, Person.Name, CompleteCount, CompleteEstTime,"
                                            "CompleteFactTime, IncompleteCount,\
                    IncompleteEstTime, IncompleteFactTime, CompleteHelpTime, CompleteHelpCount, IncompleteHelpTime,\
                    IncompleteHelpCount, Job.CodeReturns, Job.CodeDiscussion, Job.CodeBranches, Job.CodeMerged,\
                    Job.CodeSeen, Job.CodeCommented, sum(JobTime) FROM Job,\
                    Person LEFT JOIN JobTime ON Person.PersonID=JobTime.PersonID AND DATE(JobDate) BETWEEN '2017-06-26'\
                    AND '2017-07-08' WHERE Job.SprintID=") + std::to_string(sprintID) +
                                (" AND Job.PersonID=Person.PersonID GROUP BY Person.PersonID;"));
    std::cout << s << std::endl;
    mysql_query(connector, s.c_str());
    vector<unities::JobsForSprint> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            std::cout << (row[18] == NULL) << std::endl;
            vector.push_back(unities::JobsForSprint(row));
        }
        mysql_free_result(res);
    }
    return vector;

}

vector<unities::JobsForPerson> getJobsForPerson() {}

vector<unities::SprintBase> DBConnector::getSprints() {
    mysql_query(connector, "SELECT DISTINCT  Sprint.SprintID, Name FROM Sprint,Job where Sprint.SprintID=Job.SprintID \
                                ORDER BY Sprint.SprintBegin DESC;");
    vector<unities::SprintBase> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::SprintBase(row));
        }
        mysql_free_result(res);
    }
    return vector;
}

vector<unities::ProjectBase> DBConnector::getProjects() {
    mysql_query(connector, "select DISTINCT Project.ProjectID, Project.Name from Project,Sprint,Job where \
                               Project.ProjectID=Sprint.ProjectID AND Sprint.SprintID=Job.SprintID order by Sprint.SprintBegin DESC;");
    vector<unities::ProjectBase> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::ProjectBase(row));
        }
        mysql_free_result(res);
    }
    return vector;
}

vector<unities::PersonBase> DBConnector::getPersons() {
    mysql_query(connector, "SELECT PersonID, Name FROM Person ORDER BY Person.Name;");
    vector<unities::PersonBase> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::PersonBase(row));
        }
        mysql_free_result(res);
    }
    return vector;
}

vector<unities::SprintBase> DBConnector::getSprintsForProject(int id) {
    mysql_query(connector, std::string(std::string("SELECT DISTINCT  Sprint.SprintID, Name FROM Sprint,Job where \
                                           Sprint.SprintID=Job.SprintID AND Sprint.ProjectID=") + std::to_string(id) +
                                       (" ORDER BY Sprint.SprintBegin DESC;")).c_str());
    vector<unities::SprintBase> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::SprintBase(row));
        }
        mysql_free_result(res);
    }
    return vector;
}
