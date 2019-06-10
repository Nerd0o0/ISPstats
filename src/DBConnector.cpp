#include "../include/DBConnector.h"
#include <boost/algorithm/string.hpp>
#include <istream>

using namespace std;
string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
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
    /*string l;
    int projects = 1;
    int persons = 1;
    int sprints = 1;
    unities::ProjectBase project;
    unities::SprintBase sprint;
    boost::gregorian::date sprintBegin;
    boost::gregorian::date sprintEnd;
    while (!stream.eof()) {
        stream >> l;
        std::vector<std::string> line;
        boost::algorithm::split(line, l, boost::is_any_of(":"));
        std::cout << line.size() << std::endl;
        if (line[0] == "Project") {
            project(projects, boost::trim(line[1]));
            mysql_query(connector, std::string("INSERT INTO Project(Name) VALUES ('" + std::to_string(project.name) + "');");
        } else if (line[0] == "Sprint") {
            std::vector<std::string> args;
            boost::algorithm::split(args, line[1], boost::is_any_of("-"));

            sprintBegin = boost::gregorian::from_string(begin_s)
                    LocalDate.of(Integer.parseInt(args[0].trim()), Integer.parseInt(args[1].trim()),
                                 Integer.parseInt(args[2].trim()));
            end = LocalDate.of(Integer.parseInt(args[3].trim()), Integer.parseInt(args[4].trim()),
                               Integer.parseInt(args[5].trim()));
            sprintName = arr[2].trim();
            break;
        } else if (result[0] == "Sprint details") {
            args = arr[1].split(" ");
            currentSprint = new Sprint(sprints.size() + 1, currentProject.getProjectID(), sprintName,
                                       Date.valueOf(begin), Date.valueOf(end),
                                       Integer.parseInt(args[1].split("=")[1].trim()),
                                       (int) Double.parseDouble(args[2].split("=")[1].trim()),
                                       Integer.parseInt(args[3].split("=")[1].trim()),
                                       (int) Double.parseDouble(args[4].split("=")[1].trim()),
                                       (int) Double.parseDouble(args[5].split("=")[1].trim()),
                                       Integer.parseInt(args[6].split("=")[1].trim()),
                                       (int) Double.parseDouble(args[7].split("=")[1].trim()),
                                       (int) Double.parseDouble(args[8].split("=")[1].trim()),
                                       Integer.parseInt(args[9].split("=")[1].trim()),
                                       Integer.parseInt(args[10].split("=")[1].trim()),
                                       Integer.parseInt(args[11].split("=")[1].trim()));
            statement.executeQuery(
                    "INSERT INTO Sprint(ProjectID, Name, SprintBegin, SprintEnd, BugCount, EstimationBugTime," +
                    "CompleteBugCount, CompleteBugEstimation, CompleteBugFact, IncompleteBugCount, IncompleteBugEstimation," +
                    "IncompleteBugFact,CodeBranches,CodeDiscussion, CodeReturns) VALUES ('" +
                    currentSprint.getProjectID() + "', '" + currentSprint.getName() + "', '" +
                    currentSprint.getBegin() + "', '" +
                    currentSprint.getEnd() + "', '" + currentSprint.getBugCount() + "', '" +
                    currentSprint.getEstimationBugTime() + "', '" +
                    currentSprint.getCompleteBugCount() + "', '" + currentSprint.getCompleteBugEstimation() +
                    "', '" +
                    currentSprint.getCompleteBugFact() + "', '" + currentSprint.getIncompleteBugCount() + "', '" +
                    currentSprint.getIncompleteBugEstimation() + "', '" + currentSprint.getIncompleteBugFact() +
                    "', '" +
                    currentSprint.getCodeBranches() + "', '" + currentSprint.getCodeDiscussion() + "', '" +
                    currentSprint.getCodeReturns() + "');");
            //замена ID
            resultSet = statement.executeQuery(
                    "SELECT * FROM Sprint WHERE Name='" + currentSprint.getName() + "';");
            if (resultSet.next()) {
                currentSprint.setSprintID(resultSet.getInt("SprintID"));
                sprints.add(currentSprint);
            }
            break;
        } else if (result[0] == "Work") {
            args = s.split(" ");
            String[]
            date = args[2].split("-");
            String[]
            time = args[3].split(",");
            String[]
            timeStart = time[1].split(":");
            String[]
            timeEnd = time[2].split(":");
            LocalDate jobDate = LocalDate.of(Integer.parseInt(date[0]), Integer.parseInt(date[1]),
                                             Integer.parseInt(date[2]));

            LocalTime jobBegin = LocalTime.of(Integer.parseInt(timeStart[0]), Integer.parseInt(timeStart[1]),
                                              Integer.parseInt((timeStart[2])));
            LocalTime jobEnd = LocalTime.of(Integer.parseInt(timeEnd[0]), Integer.parseInt(timeEnd[1]),
                                            Integer.parseInt(timeEnd[2]));
            JobTime jobTime = new JobTime(getPersonFromName(args[1]).getPersonID(),
                                          Integer.parseInt(time[0].trim()),
                                          (jobBegin.getHour() * 3600) + (jobBegin.getMinute() * 60) +
                                          jobBegin.getSecond(),
                                          (jobEnd.getHour() * 3600) + (jobEnd.getMinute() * 60) +
                                          jobEnd.getSecond(),
                                          jobDate);
            jobTimes.add(jobTime);
            statement.executeQuery("INSERT INTO JobTime(PersonID, JobTime, JobBegin, JobEnd, JobDate) VALUES ('" +
                                   jobTime.personID + "', '" + jobTime.jobTime + "', '" + jobTime.jobBegin +
                                   "', '" +
                                   jobTime.jobEnd + "', '" + jobTime.jobDate + "');");
            break;
        } else if (result[0] == "" || result[0] == "Process finished with exit code 0") {}
        else {
            args = s.split(" ");
            Person person = getPersonFromName(args[0]);
            if (person == null) {
                person = new Person(currentProject.getProjectID(), persons.size() + 1, args[0]);
                statement.executeQuery(
                        "INSERT INTO Person(ProjectID, Name) VALUES ('" + person.getProjectID() + "', '" +
                        person.getPersonName() + "');");
                //замена ID
                resultSet = statement.executeQuery(
                        "SELECT * FROM Person WHERE Name='" + person.getPersonName() + "';");
                if (resultSet.next()) {
                    person.setPersonID(resultSet.getInt("PersonID"));
                }
                persons.add(person);
            }
            Job job = new Job(person.getPersonID(),
                              currentSprint,//Sprint sprint;
                              Integer.parseInt(args[2].split("=")[1].trim()),//int completeCount;
                              (int) Double.parseDouble(args[3].split("=")[1].trim()),//int completeEstTime;
                              (int) Double.parseDouble(args[4].split("=")[1].trim()),//int completeFactTime;
                              Integer.parseInt(args[5].split("=")[1].trim()),//int incompleteCount;
                              (int) Double.parseDouble(args[6].split("=")[1].trim()),//int incompleteEstTime;
                              (int) Double.parseDouble(args[7].split("=")[1].trim()),//int incompleteFactTime;
                              (int) Double.parseDouble(args[8].split("=")[1].trim()),//int completeHelpTime;
                              Integer.parseInt(args[9].split("=")[1].trim()),//int completeHelpCount;
                              (int) Double.parseDouble(args[10].split("=")[1].trim()),//int incompleteHelpTime;
                              Integer.parseInt(args[11].split("=")[1].trim()),//int incompleteHelpCount;
                              Integer.parseInt(args[12].split("=")[1].trim()),//int codeReturns;
                              Integer.parseInt(args[13].split("=")[1].trim()),//int codeDiscussion;
                              Integer.parseInt(args[14].split("=")[1].trim()),//int codeBranches;
                              Integer.parseInt(args[15].split("=")[1].trim()),//int codeMerged;
                              Integer.parseInt(args[16].split("=")[1].trim()),//int codeSeen;
                              Integer.parseInt(args[17].split("=")[1].trim()));//int codeCommented;
            statement.executeQuery("INSERT INTO Job(PersonID, SprintID," +
                                   "CompleteCount, CompleteEstTime,CompleteFactTime," +
                                   "IncompleteCount, IncompleteEstTime, IncompleteFactTime," +
                                   "CompleteHelpTime, CompleteHelpCount," +
                                   "IncompleteHelpTime, IncompleteHelpCount," +
                                   "CodeReturns, CodeDiscussion, CodeBranches, CodeMerged," +
                                   "CodeSeen, CodeCommented) VALUES ('" +
                                   job.getPersonID() + "', '" + job.getSprint().getSprintID() + "', '" +
                                   job.getCompleteCount() + "', '" + job.getCompleteEstTime() + "', '" +
                                   job.getCompleteFactTime() + "', '" +
                                   job.getIncompleteCount() + "', '" + job.getIncompleteEstTime() + "', '" +
                                   job.getIncompleteFactTime() + "', '" +
                                   job.getCompleteHelpTime() + "', '" + job.getCompleteHelpCount() + "', '" +
                                   job.getIncompleteHelpTime() + "', '" + job.getIncompleteHelpCount() + "', '" +
                                   job.getCodeReturns() + "', '" + job.getCodeDiscussion() + "', '" +
                                   job.getCodeBranches() + "', '" + job.getCodeMerged() + "', '" +
                                   job.getCodeSeen() + "', '" + job.getCodeCommented() + "')");
            jobs.add(job);
            break;
        }
    }*/
    return 0;
}
