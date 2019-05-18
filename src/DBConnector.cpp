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
    std::string query="SELECT SprintID, Project.Name, Sprint.Name, Sprint.SprintBegin, Sprint.SprintEnd, BugCount,\
                      EstimationBugTime, CompleteBugCount, CompleteBugEstimation, CompleteBugFact, \
                      IncompleteBugCount, IncompleteBugEstimation, IncompleteBugFact, CodeBranches, \
                      CodeDiscussion, CodeReturns \
                      FROM Sprint, Project WHERE Sprint.ProjectID=Project.ProjectID \
                      ORDER BY Sprint.SprintBegin desc;";
    mysql_query(connector, query.c_str());
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
    std::string query = "SELECT Person.PersonID, Person.Name, CompleteCount, CompleteEstTime,"
                    "CompleteFactTime, IncompleteCount, IncompleteEstTime, IncompleteFactTime,\
                    CompleteHelpTime, CompleteHelpCount, IncompleteHelpTime, IncompleteHelpCount,\
                    Job.CodeReturns, Job.CodeDiscussion, Job.CodeBranches, Job.CodeMerged,\
                    Job.CodeSeen, Job.CodeCommented, sum(JobTime) FROM Job,\
                    Person LEFT JOIN JobTime ON Person.PersonID=JobTime.PersonID AND DATE(JobDate)\
                    BETWEEN (SELECT SprintBegin from Sprint where SprintID="+std::to_string(sprintID)+
                    ") AND (SELECT SprintEnd from Sprint where SprintID="+std::to_string(sprintID)+
                    ") WHERE Job.SprintID="+std::to_string(sprintID)+
                    " AND Job.PersonID=Person.PersonID GROUP BY Person.PersonID;";
    std::cout<<query<<std::endl;
    mysql_query(connector, query.c_str());
    vector<unities::JobsForSprint> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::JobsForSprint(row));
        }
        mysql_free_result(res);
    }
    return vector;}
    //SELECT Person.PersonID, Person.Name, CompleteCount, CompleteEstTime, CompleteFactTime, IncompleteCount, IncompleteEstTime, IncompleteFactTime, CompleteHelpTime, CompleteHelpCount, IncompleteHelpTime, IncompleteHelpCount, Job.CodeReturns, Job.CodeDiscussion, Job.CodeBranches, Job.CodeMerged, Job.CodeSeen, Job.CodeCommented, sum(JobTime) FROM Job, Person LEFT JOIN JobTime ON Person.PersonID=JobTime.PersonID AND DATE(JobDate) BETWEEN (SELECT SprintBegin from Sprint where SprintID=1) AND (SELECT SprintEnd from Sprint where SprintID=1) WHERE Job.SprintID=1 AND Job.PersonID=Person.PersonID GROUP BY Person.PersonID;

vector<unities::JobsForPerson> DBConnector::getJobsForPerson(int person_id) {
    std::string query = "select Project, Name, JobId, sum(JobTime) from (select Project.Name as Project, Job.PersonID as PersonID, Sprint.Name, SprintBegin, SprintEnd, Job.JobID from Project, Sprint, Job, JobTime where Project.ProjectID=Sprint.ProjectID AND Sprint.SprintID=Job.SprintID AND JobTime.PersonID=27 AND Job.PersonID=27 group by Sprint.SprintID) AS a left join JobTime on a.PersonID=JobTime.PersonID AND JobDate between SprintBegin and SprintEnd group by Name;"
    mysql_query(connector, query.c_str());
    vector<unities::JobsForPerson> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::JobsForPerson(row));
        }
        mysql_free_result(res);
    }
    return vector;
}

vector<unities::SprintBase> DBConnector::getSprints() {
    std::string query="SELECT DISTINCT Sprint.SprintID, Name FROM Sprint,Job \
                    WHERE Sprint.SprintID=Job.SprintID \
                    ORDER BY Sprint.SprintBegin DESC;";
    mysql_query(connector, query.c_str());
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
    std::string query="SELECT DISTINCT Project.ProjectID, Project.Name FROM Project,Sprint,Job WHERE "
                      "Project.ProjectID=Sprint.ProjectID AND Sprint.SprintID=Job.SprintID \
                      ORDER BY Sprint.SprintBegin DESC;";
    mysql_query(connector, query.c_str());
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
vector<unities::ProjectBase> DBConnector::getProjectForSprint(int sprint_id) {
    std::string query="SELECT DISTINCT Project.ProjectID, Project.Name FROM Project,Sprint WHERE "
                      "Project.ProjectID=Sprint.ProjectID AND Sprint.SprintID="+
                      std::to_string(sprint_id)+";";
    mysql_query(connector, query.c_str());
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
    std::string query="SELECT PersonID, Name FROM Person ORDER BY Person.Name ORDER BY Person.Name;";
    mysql_query(connector, query.c_str());
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
    std::string query="SELECT DISTINCT  Sprint.SprintID, Name FROM Sprint,Job WHERE "
                      "Sprint.SprintID=Job.SprintID AND Sprint.ProjectID=" + std::to_string(id) +
                      " ORDER BY Sprint.SprintBegin DESC;";
    mysql_query(connector, query.c_str());
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
