//
// Created by nerd on 02.05.19.
//

#include "../include/mysql.h"
#include <stdlib.h>
#include <iostream>
#include "../unities/include/ProjectBase.h"
#include "../unities/include/SprintBase.h"
#include "../unities/include/PersonBase.h"
#include "../unities/include/SprintsAndProjects.h"
#include "../unities/include/JobsForSprint.h"
#include "../unities/include/JobsForPerson.h"
using namespace std;
class DBConnector {
public:
    DBConnector() {
        mysql_debug("d:t:O");
        try {
            connector = mysql_init(NULL);

        } catch (std::exception &e) {
            cout << "err" << endl;
            cout << e.what() << endl;
        }


        if (!mysql_real_connect(connector, "localhost", "stats", "q1w2e3r4",
                                "statsDB", 3306, NULL/*"/var/run/mysqld/mysqld.sock"*/, 0) &&
                                mysql_set_character_set(connector,"utf8")){
            printf("Error(%d) [%s] \"%s\"", mysql_errno(connector),
                   mysql_sqlstate(connector),
                   mysql_error(connector));
            mysql_close(connector);
            exit(-1);
        }
        mysql_query(connector,"SELECT * FROM ProjectBase");
        if(res = mysql_store_result(connector)){
            while(row=mysql_fetch_row(res)){
                for(int i=0;i<mysql_num_fields(res);i++){
                    std::cout<<row[i]<<" ";
                }
                std::cout<<std::endl;
            }

            mysql_free_result(res);
        }
    }

    ~DBConnector() {
        mysql_close(connector);
    }

    vector<unities::SprintsAndProjects> getSprintsAndProjects(){
        mysql_query(connector,"select SprintID Project.Name, Sprint.Name, BugCount, EstimationBugTime, CompleteBugCount,"
                              "CompleteBugEstimation, CompleteBugFact, IncompleteBugCount, IncompleteBugEstimation, IncompleteBugFact,"
                              "CodeReturns, CodeDiscussion from Sprint, Project where Sprint.ProjectID=Project.ProjectID;");
        vector<unities::SprintsAndProjects> vector;
        if(res = mysql_store_result(connector)) {
            //vector.resize(mysql_num_rows(res));
            while (row = mysql_fetch_row(res)) {
                vector.push_back(unities::SprintsAndProjects(row));
            }
            mysql_free_result(res);
        }return vector;
    }
    vector<unities::JobsForSprint> getJobsForSprints(int sprintID){
        //s=std::strcat(*s," );
        mysql_query(connector,std::string(std::string("SELECT Person.PersonID, Person.Name, CompleteCount, CompleteEstTime, CompleteFactTime, IncompleteCount,\
                    IncompleteEstTime, IncompleteFactTime, CompleteHelpTime, CompleteHelpCount, IncompleteHelpTime,\
                    IncompleteHelpCount, Job.CodeReturns, Job.CodeDiscussion, Job.CodeBranches, Job.CodeMerged,\
                    Job.CodeSeen, Job.CodeCommented, sum(JobTime) FROM Job,\
                    Person LEFT JOIN JobTime ON Person.PersonID=JobTime.PersonID AND DATE(JobDate) BETWEEN '2017-06-26'\
                    AND '2017-07-08' WHERE Job.SprintID=")+std::to_string(sprintID)+(" AND Job.PersonID=Person.PersonID GROUP BY Person.PersonID;")).c_str());
        vector<unities::JobsForSprint> vector;
        if(res = mysql_store_result(connector)) {
            //vector.resize(mysql_num_rows(res));
            while (row = mysql_fetch_row(res)) {
                vector.push_back(unities::JobsForSprint(row));
            }
            mysql_free_result(res);
        }return vector;

    }
    vector<unities::JobsForPerson> getJobsForPerson(){

    }
    vector<unities::SprintBase> getSprints() {
        mysql_query(connector, "SELECT DISTINCT  Sprint.SprintID, Name FROM Sprint,Job where Sprint.SprintID=Job.SprintID;;");
        vector<unities::SprintBase> vector;
        if (res = mysql_store_result(connector)) {
            //vector.resize(mysql_num_rows(res));
            while(row = mysql_fetch_row(res)){
                vector.push_back(unities::SprintBase(row));
            }
            mysql_free_result(res);
        }return vector;
    }
    vector<unities::ProjectBase> getProjects() {
        mysql_query(connector, "SELECT DISTINCT Project.ProjectID, Project.Name FROM Project,Sprint where Project.ProjectID=Sprint.ProjectID;");
        vector<unities::ProjectBase> vector;
        if (res = mysql_store_result(connector)) {
            //vector.resize(mysql_num_rows(res));
            while(row = mysql_fetch_row(res)){
                vector.push_back(unities::ProjectBase(row));
            }
            mysql_free_result(res);
        }return vector;
    }
    vector<unities::PersonBase> getPersons() {
        mysql_query(connector, "SELECT PersonID, Name FROM Person;");
        vector<unities::PersonBase> vector;
        if (res = mysql_store_result(connector)) {
            //vector.resize(mysql_num_rows(res));
            while(row = mysql_fetch_row(res)){
                vector.push_back(unities::PersonBase(row));
            }
            mysql_free_result(res);
        }return vector;
    }

private:
    MYSQL *connector;
    MYSQL_RES *res;
    MYSQL_ROW row;

};
