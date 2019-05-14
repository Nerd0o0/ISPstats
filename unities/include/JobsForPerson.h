#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <nlohmann/json.hpp>

namespace unities {
    using namespace std;
    class JobsForPerson {
    public:
        int jobID;
        string project;
        int sprintID;
        string sprint;
        int completeCount;
        int completeEstTime;
        int completeFactTime;
        int incompleteCount;
        int incompleteEstTime;
        int incompleteFactTime;
        int completeHelpTime;
        int completeHelpCount;
        int incompleteHelpTime;
        int incompleteHelpCount;
        int codeReturns;
        int codeDiscussion;
        int codeBranches;
        int codeMerged;
        int codeSeen;
        int codeCommented;
        int workTime;
        JobsForPerson(int job_id, string project_name, int sprint_id, string sprint_name,int complete_count,int complete_est_time, int complete_fact_time,
                int incomplete_count,int incomplete_est_time, int incomplete_fact_time, int complete_help_time,
                int complete_help_count, int incomplete_help_time, int incomplete_help_count, int code_returns,
                int code_discussion, int code_branches, int code_merged, int code_seen, int code_commented,int work_time):
                jobID(job_id),project(project_name), sprintID(sprint_id), sprint(sprint_name),completeCount(complete_count),
                completeEstTime(complete_est_time),completeFactTime(complete_fact_time),
                incompleteCount(incomplete_count),incompleteEstTime(incomplete_est_time),
                incompleteFactTime(incomplete_fact_time),completeHelpTime(complete_help_time),
                completeHelpCount(complete_help_count),incompleteHelpTime(incomplete_help_time),
                incompleteHelpCount(incomplete_help_count),codeReturns(code_returns),codeDiscussion(code_discussion),
                codeBranches(code_branches),codeMerged(code_merged),codeSeen(code_seen),
                codeCommented(code_commented),workTime(work_time){}
        JobsForPerson(char **rows):JobsForPerson(stoi(rows[0]),rows[1],stoi(rows[2]), rows[3],stoi(rows[4]),stoi(rows[5]),stoi(rows[6]),
                stoi(rows[7]),stoi(rows[8]),stoi(rows[9]),stoi(rows[10]),
                stoi(rows[11]),stoi(rows[12]),stoi(rows[13]),stoi(rows[14]),
                stoi(rows[15]),stoi(rows[16]),stoi(rows[17]),stoi(rows[18]),stoi(rows[19]),stoi(rows[20])){}
    };

    inline void to_json(nlohmann::json &j, const JobsForPerson &p) {
        j = nlohmann::json{
                {"jobID",               p.jobID},
                {"project",             p.project},
                {"sprintID",            p.sprintID},
                {"sprint",              p.sprint},
                {"completeCount",       p.completeCount},
                {"completeEstTime",     p.completeEstTime},
                {"completeFactTime",    p.completeFactTime},
                {"incompleteCount",     p.incompleteCount},
                {"incompleteEstTime",   p.incompleteEstTime},
                {"incompleteFactTime",  p.incompleteFactTime},
                {"completeHelpTime",    p.completeHelpTime},
                {"completeHelpCount",   p.completeHelpCount},
                {"incompleteHelpTime",  p.incompleteHelpTime},
                {"incompleteHelpCount", p.incompleteHelpCount},
                {"codeReturns",         p.codeReturns},
                {"codeDiscussion",      p.codeDiscussion},
                {"codeBranches",        p.codeBranches},
                {"codeMerged",          p.codeMerged},
                {"codeSeen",            p.codeSeen},
                {"codeCommented",       p.codeCommented},
                {"workTime",            p.workTime}

        };
    }

    inline void from_json(const nlohmann::json &j, JobsForPerson &p) {
        j.at("jobID").get_to(p.jobID);
        j.at("project").get_to(p.project);
        j.at("sprintID").get_to(p.sprintID);
        j.at("sprint").get_to(p.sprint);
        j.at("completeCount").get_to(p.completeCount);
        j.at("completeEstTime").get_to(p.completeEstTime);
        j.at("completeFactTime").get_to(p.completeFactTime);
        j.at("incompleteCount").get_to(p.incompleteCount);
        j.at("incompleteEstTime").get_to(p.incompleteEstTime);
        j.at("incompleteFactTime").get_to(p.incompleteFactTime);
        j.at("completeHelpTime").get_to(p.completeHelpTime);
        j.at("completeHelpCount").get_to(p.completeHelpCount);
        j.at("incompleteHelpTime").get_to(p.incompleteHelpTime);
        j.at("incompleteHelpCount").get_to(p.incompleteHelpCount);
        j.at("codeReturns").get_to(p.codeReturns);
        j.at("codeDiscussion").get_to(p.codeDiscussion);
        j.at("codeBranches").get_to(p.codeBranches);
        j.at("codeMerged").get_to(p.codeMerged);
        j.at("codeSeen").get_to(p.codeSeen);
        j.at("codeCommented").get_to(p.codeCommented);
        j.at("workTime").get_to(p.workTime);
    }
}
