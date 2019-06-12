#include "../include/DBConnector.h"
#include <boost/algorithm/string.hpp>
#include <istream>
#include <string>
#include <locale>
#include <clocale>
#include <boost/format.hpp>

using namespace std;
string trim(const string& str)
{
    if(str.length()==0) return str;
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
vector<std::string> split(string str, const string sep){
    std::vector<std::string> arr;
    boost::algorithm::split(arr, str, boost::is_any_of(sep));
    return arr;
}
std::string getPersonByName(MYSQL *connector, std::string name) {
    mysql_query(connector, std::string("SELECT PersonID FROM Person WHERE Name=" + name).c_str());
    string personID;
    MYSQL_RES *res;
    if (res = mysql_store_result(connector)) {
        while (MYSQL_ROW row = mysql_fetch_row(res)) {
            personID = row[0];
        }
        mysql_free_result(res);
    }
    return personID;
}
DBConnector::DBConnector():DBConnector("stats","q1w2e3r4") {}
DBConnector::DBConnector(string login, string password){
    mysql_debug("d:t:O");
    try {
        connector = mysql_init(NULL);

    } catch (std::exception &e) {
        cout << "err" << endl;
        cout << e.what() << endl;
    }


    if (!mysql_real_connect(connector, "localhost", login.c_str(), password.c_str(),
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
    std::string query="SELECT SprintID, Project.Name, Sprint.Name, Sprint.SprintBegin, Sprint.SprintEnd, BugCount, \
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
    std::string query = "SELECT Person.PersonID, Person.Name, CompleteCount, CompleteEstTime,CompleteFactTime,\
                        IncompleteCount, IncompleteEstTime, IncompleteFactTime, CompleteHelpTime, CompleteHelpCount,\
                        IncompleteHelpTime, IncompleteHelpCount,Job.CodeReturns, Job.CodeDiscussion, Job.CodeBranches,\
                        Job.CodeMerged,Job.CodeSeen, Job.CodeCommented, sum(JobTime) FROM Job, Person \
                        LEFT JOIN JobTime ON Person.PersonID=JobTime.PersonID AND DATE(JobDate)\
                        BETWEEN (SELECT SprintBegin from Sprint where SprintID="+std::to_string(sprintID)+
                        ") AND (SELECT SprintEnd from Sprint where SprintID="+std::to_string(sprintID)+
                        ") WHERE Job.SprintID="+std::to_string(sprintID)+
                        " AND Job.PersonID=Person.PersonID GROUP BY Person.PersonID;";
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
    std::string query = "SELECT Project, SprintID, Sprint,CompleteCount,CompleteEstTime,CompleteFactTime,\
                       IncompleteCount,IncompleteEstTime,IncompleteFactTime,CompleteHelpTime,CompleteHelpCount,\
                       IncompleteHelpTime,IncompleteHelpCount,CodeReturns,CodeDiscussion,CodeBranches,CodeMerged,\
                       CodeSeen,CodeCommented, sum(JobTime) FROM \
                       (SELECT Project.Name as Project, Sprint.SprintID, Job.PersonID as PersonID,\
                       Sprint.Name as Sprint, CompleteCount, CompleteEstTime,CompleteFactTime,IncompleteCount,\
                       IncompleteEstTime,IncompleteFactTime, CompleteHelpTime,CompleteHelpCount, IncompleteHelpTime,\
                       IncompleteHelpCount,Job.CodeReturns,Job.CodeDiscussion,Job.CodeBranches,Job.CodeMerged,\
                       CodeSeen,CodeCommented, SprintBegin, SprintEnd, Job.JobID FROM Project, Sprint, Job, JobTime \
                       WHERE Project.ProjectID=Sprint.ProjectID AND Sprint.SprintID=Job.SprintID AND \
                       JobTime.PersonID="+std::to_string(person_id) + " AND Job.PersonID="+std::to_string(person_id) +
                       " GROUP BY Sprint.SprintID) AS a LEFT JOIN JobTime \
                       ON a.PersonID=JobTime.PersonID AND JobDate BETWEEN SprintBegin AND SprintEnd GROUP BY Sprint;";
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

vector<unities::Base> DBConnector::getProjects() {
    std::string query="SELECT DISTINCT Project.ProjectID, Project.Name FROM Project,Sprint,Job WHERE \
                      Project.ProjectID=Sprint.ProjectID AND Sprint.SprintID=Job.SprintID \
                      ORDER BY Sprint.SprintBegin DESC;";
    mysql_query(connector, query.c_str());
    vector<unities::Base> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::Base(row));
        }
        mysql_free_result(res);
    }
    return vector;
}
vector<unities::Base> DBConnector::getProjectForSprint(int sprint_id) {
    std::string query="SELECT DISTINCT Project.ProjectID, Project.Name FROM Project,Sprint WHERE \
                      Project.ProjectID=Sprint.ProjectID AND Sprint.SprintID="+
                      std::to_string(sprint_id)+";";
    mysql_query(connector, query.c_str());
    vector<unities::Base> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::Base(row));
        }
        mysql_free_result(res);
    }
    return vector;
}
vector<unities::Base> DBConnector::getPersons() {
    std::string query="SELECT PersonID, Name FROM Person ORDER BY Name;";
    mysql_query(connector, query.c_str());
    vector<unities::Base> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::Base(row));
        }
        mysql_free_result(res);
    }
    return vector;
}

vector<unities::Base> DBConnector::getSprintsForProject(int id) {
    std::string query="SELECT DISTINCT  Sprint.SprintID, Name FROM Sprint,Job WHERE \
                      Sprint.SprintID=Job.SprintID AND Sprint.ProjectID=" + std::to_string(id) +
                      " ORDER BY Sprint.SprintBegin DESC;";
    mysql_query(connector, query.c_str());
    vector<unities::Base> vector;
    if (res = mysql_store_result(connector)) {
        //vector.resize(mysql_num_rows(res));
        while (row = mysql_fetch_row(res)) {
            vector.push_back(unities::Base(row));
        }
        mysql_free_result(res);
    }
    return vector;
}
vector<unities::LeaderPerson> DBConnector::getMinRatioPersons() {
    std::string query = "select a.PersonID, Person.Name, ratio from (select PersonID, SprintID, \
                        avg(completeFactTime/completeEstTime) as ratio from Job group by PersonID) as a, \
                        Person where ratio>0 AND a.PersonID=Person.PersonID order by ratio limit 5;";
    vector<unities::LeaderPerson> vector;
    mysql_query(connector, query.c_str());
    if (res = mysql_store_result(connector)) {
        while(row = mysql_fetch_row(res)) {
            vector.push_back(unities::LeaderPerson(row));
        }
        mysql_free_result(res);
    }
    return vector;
}
int DBConnector::initDatabase() {
    std::string query = "drop table if exist Project;\
                        create table Project( \
                        ProjectID INT AUTO_INCREMENT,\
                        Name VARCHAR(255),\
                        PRIMARY KEY (ProjectID));\
                        ALTER TABLE Project CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        ALTER TABLE Project DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        \
                        drop table if exist Person\
                        create table Person(\
                        PersonID INT AUTO_INCREMENT,\
                        ProjectID INT,\
                        Name VARCHAR(255),\
                        PRIMARY KEY (PersonID),\
                        FOREIGN KEY (ProjectID) REFERENCES Project(ProjectID));\
                        ALTER TABLE Person CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        ALTER TABLE Person DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        \
                        drop table if exist Sprint\
                        create table Sprint(\
                        SprintID INT AUTO_INCREMENT,\
                        ProjectID INT NOT NULL,\
                        Name VARCHAR(255),\
                        SprintBegin DATE,\
                        SprintEnd DATE,\
                        BugCount INT,\
                        EstimationBugTime INT,\
                        CompleteBugCount INT,\
                        CompleteBugEstimation INT,\
                        CompleteBugFact INT,\
                        IncompleteBugCount INT,\
                        IncompleteBugEstimation INT,\
                        IncompleteBugFact INT,\
                        CodeBranches INT,\
                        CodeDiscussion INT,\
                        CodeReturns INT,\
                        PRIMARY KEY (SprintID),\
                        FOREIGN KEY (ProjectID) REFERENCES Project(ProjectID));\
                        ALTER TABLE Sprint CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        ALTER TABLE Sprint DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        \
                        drop table if exist Job\
                        create table Job(\
                        JobID INT AUTO_INCREMENT,\
                        PersonID INT NOT NULL,\
                        SprintID INT NOT NULL,\
                        CompleteCount INT,\
                        CompleteEstTime INT,\
                        CompleteFactTime INT,\
                        IncompleteCount INT,\
                        IncompleteEstTime INT,\
                        IncompleteFactTime INT,\
                        CompleteHelpTime INT,\
                        CompleteHelpCount INT,\
                        IncompleteHelpTime INT,\
                        IncompleteHelpCount INT,\
                        CodeReturns INT,\
                        CodeDiscussion INT,\
                        CodeBranches INT,\
                        CodeMerged INT,\
                        CodeSeen INT,\
                        CodeCommented INT,\
                        PRIMARY KEY (JobID),\
                        FOREIGN KEY (PersonID) REFERENCES Person(PersonID),\
                        FOREIGN KEY (SprintID) REFERENCES Sprint(SprintID));\
                        ALTER TABLE Job CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        ALTER TABLE Job DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        \
                        drop table if exist JobTime\
                        create table JobTime(\
                        JobTimeID INT AUTO_INCREMENT,\
                        PersonID INT NOT NULL,\
                        JobTime INT,\
                        JobBegin INT,\
                        JobEnd INT,\
                        JobDate DATE NOT NULL,\
                        PRIMARY KEY (JobTimeID, PersonID),\
                        FOREIGN KEY (PersonID) REFERENCES Person(PersonID));\
                        ALTER TABLE JobTime CONVERT TO CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        ALTER TABLE JobTime DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;\
                        ";
    return mysql_query(connector, query.c_str());
}
int DBConnector::loadData(std::istream& stream) {
    string l;
    string query;
    int projects = 0;
    int persons = 0;
    int sprints = 0;
    unities::Base project;
    unities::Base sprint;
    boost::gregorian::date sprintBegin;
    boost::gregorian::date sprintEnd;
    while (!stream.eof()) {
        std::getline(stream,l,'\n');
        std::vector<std::string> line=split(l,":");
        if (line[0].compare("Project")==0) {
            project = unities::Base(projects+1, trim(line[1]));
            query=std::string("INSERT INTO Project(Name) VALUES (")+string(trim(line[1]))+string(");");
            mysql_query(connector, std::string("INSERT INTO Project(Name) VALUES ('" + trim(line[1]) + "');").c_str());
            projects++;
        } else if (line[0] == "Sprint") {
            std::vector<std::string> args=split(line[1],"-");
            sprintBegin = boost::gregorian::from_string(trim(args[0]) + "-" + trim(args[1]) + "-" + trim(args[2]));
            sprintEnd = boost::gregorian::from_string(trim(args[3]) + "-" + trim(args[4]) + "-" + trim(args[5]));
            sprint=unities::Base(sprints+1, trim(args[2]));
            break;
        } else if (line[0] == "Sprint details") {
            std::vector<std::string> args=split(line[1]," ");
            mysql_query(connector, std::string("INSERT INTO Sprint \
                                                   (ProjectID, Name, SprintBegin, SprintEnd, BugCount, EstimationBugTime,\
                                                   CompleteBugCount, CompleteBugEstimation, CompleteBugFact, IncompleteBugCount,\
                                                   IncompleteBugEstimation,IncompleteBugFact,CodeBranches,CodeDiscussion,\
                                                   CodeReturns) VALUES ('" + std::to_string(projects) + ","+ sprint.name +
                                               (std::to_string(sprintBegin.year())+"-"+std::to_string(sprintBegin.month())+"-"+std::to_string(sprintBegin.day()))+
                                               ","+(std::to_string(sprintEnd.year())+"-"+std::to_string(sprintEnd.month())+"-"+std::to_string(sprintEnd.day()))+
                                               ","+trim(split(args[1],"=")[1])+","+ trim(split(args[2],"=")[1])+","+
                                               trim(split(args[3],"=")[1])+","+trim(split(args[4],"=")[1])+","+
                                               trim(split(args[5],"=")[1])+","+trim(split(args[6],"=")[1])+","+
                                               trim(split(args[7],"=")[1])+","+trim(split(args[8],"=")[1])+","+
                                               trim(split(args[9],"=")[1])+","+trim(split(args[10],"=")[1])+","+
                                               trim(split(args[11],"=")[1])+");").c_str());
            std::cout<<std::string("INSERT INTO Sprint \
                                                   (ProjectID, Name, SprintBegin, SprintEnd, BugCount, EstimationBugTime,\
                                                   CompleteBugCount, CompleteBugEstimation, CompleteBugFact, IncompleteBugCount,\
                                                   IncompleteBugEstimation,IncompleteBugFact,CodeBranches,CodeDiscussion,\
                                                   CodeReturns) VALUES ('" + std::to_string(projects) + ","+ sprint.name +
                                                          (std::to_string(sprintBegin.year())+"-"+std::to_string(sprintBegin.month())+"-"+std::to_string(sprintBegin.day()))+
                                                          ","+(std::to_string(sprintEnd.year())+"-"+std::to_string(sprintEnd.month())+"-"+std::to_string(sprintEnd.day()))+
                                                          ","+trim(split(args[1],"=")[1])+","+ trim(split(args[2],"=")[1])+","+
                                                          trim(split(args[3],"=")[1])+","+trim(split(args[4],"=")[1])+","+
                                                          trim(split(args[5],"=")[1])+","+trim(split(args[6],"=")[1])+","+
                                                          trim(split(args[7],"=")[1])+","+trim(split(args[8],"=")[1])+","+
                                                          trim(split(args[9],"=")[1])+","+trim(split(args[10],"=")[1])+","+
                                                          trim(split(args[11],"=")[1])+");").c_str()<<std::endl;
            sprints++;
        } else if (line[0] == "Work") {
            std::vector<std::string> args=split(l.substr(6)," ");
            string personID=getPersonByName(connector, args[0]);
            vector<string> start=split(split(args[2],",")[1],":");
            vector<string> end=split(split(args[2],",")[2],":");
            int jobStart=stoi(start[0])*360+stoi(start[1])*60+stoi(start[2]);
            int jobEnd=stoi(end[0])*360+stoi(end[1])*60+stoi(end[2]);
            mysql_query(connector, std::string("INSERT INTO JobTime(PersonID, JobTime, JobBegin, JobEnd, JobDate) VALUES (" +
                                   personID + "," + split(args[2],",")[0] + "," + std::to_string(jobStart) +
                                   ", " + std::to_string(jobEnd) + "," + args[1] + "');").c_str());
            std::cout<<std::string("INSERT INTO JobTime(PersonID, JobTime, JobBegin, JobEnd, JobDate) VALUES (" +
                                   personID + "," + split(args[2],",")[0] + "," + std::to_string(jobStart) +
                                   ", " + std::to_string(jobEnd) + "," + args[1] + "');").c_str()<<std::endl;
        } else if (line[0] == "" || line[0] == "Process finished with exit code 0") {}
        else {
            std::vector<std::string> args=split(l," ");
            std::string personID = getPersonByName(connector, args[0]);
            if (personID == "") {
                mysql_query(connector, std::string("INSERT INTO Person(ProjectID, Name) VALUES (" + std::to_string(project.id) + "," +
                        args[0] + ");").c_str());
                std::cout<<std::string("INSERT INTO Person(ProjectID, Name) VALUES (" + std::to_string(project.id) + "," +
                       args[0] + ");").c_str()<<std::endl;
                persons++;
                personID = getPersonByName(connector, args[0]);
            }
            mysql_query(connector, std::string("INSERT INTO Job(PersonID, SprintID,\
                                   CompleteCount, CompleteEstTime,CompleteFactTime,\
                                   IncompleteCount, IncompleteEstTime, IncompleteFactTime,\
                                   CompleteHelpTime, CompleteHelpCount,\
                                   IncompleteHelpTime, IncompleteHelpCount,\
                                   CodeReturns, CodeDiscussion, CodeBranches, CodeMerged,\
                                   CodeSeen, CodeCommented) VALUES (" +
                                   personID + "," + std::to_string(sprint.id) + "," +
                                   trim(split(args[2],"=")[1]) + "," +
                                   trim(split(args[3],"=")[1]) + "," +
                                   trim(split(args[4],"=")[1]) + "," +
                                   trim(split(args[5],"=")[1]) + "," +
                                   trim(split(args[6],"=")[1]) + "," +
                                   trim(split(args[7],"=")[1]) + "," +
                                   trim(split(args[8],"=")[1]) + "," +
                                   trim(split(args[9],"=")[1]) + "," +
                                   trim(split(args[10],"=")[1]) + "," +
                                   trim(split(args[11],"=")[1]) + "," +
                                   trim(split(args[12],"=")[1]) + "," +
                                   trim(split(args[13],"=")[1]) + "," +
                                   trim(split(args[14],"=")[1]) + "," +
                                   trim(split(args[15],"=")[1]) + "," +
                                   trim(split(args[16],"=")[1]) + "," +
                                   trim(split(args[17],"=")[1]) + ");").c_str());
        std::cout<<std::string("INSERT INTO Job(PersonID, SprintID,\
                                   CompleteCount, CompleteEstTime,CompleteFactTime,\
                                   IncompleteCount, IncompleteEstTime, IncompleteFactTime,\
                                   CompleteHelpTime, CompleteHelpCount,\
                                   IncompleteHelpTime, IncompleteHelpCount,\
                                   CodeReturns, CodeDiscussion, CodeBranches, CodeMerged,\
                                   CodeSeen, CodeCommented) VALUES (" +
                               personID + "," + std::to_string(sprint.id) + "," +
                               trim(split(args[2],"=")[1]) + "," +
                               trim(split(args[3],"=")[1]) + "," +
                               trim(split(args[4],"=")[1]) + "," +
                               trim(split(args[5],"=")[1]) + "," +
                               trim(split(args[6],"=")[1]) + "," +
                               trim(split(args[7],"=")[1]) + "," +
                               trim(split(args[8],"=")[1]) + "," +
                               trim(split(args[9],"=")[1]) + "," +
                               trim(split(args[10],"=")[1]) + "," +
                               trim(split(args[11],"=")[1]) + "," +
                               trim(split(args[12],"=")[1]) + "," +
                               trim(split(args[13],"=")[1]) + "," +
                               trim(split(args[14],"=")[1]) + "," +
                               trim(split(args[15],"=")[1]) + "," +
                               trim(split(args[16],"=")[1]) + "," +
                               trim(split(args[17],"=")[1]) + ");").c_str()<<std::endl;
        }
    }
    return 0;
}


