#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <nlohmann/json.hpp>

namespace unities {
    using namespace std;

    class JobsForSprint {
    public:
        int personID;
        string person;
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

        JobsForSprint(int person_id, string person_name, int complete_count, int complete_est_time,
                      int complete_fact_time,
                      int incomplete_count, int incomplete_est_time, int incomplete_fact_time, int complete_help_time,
                      int complete_help_count, int incomplete_help_time, int incomplete_help_count, int code_returns,
                      int code_discussion, int code_branches, int code_merged, int code_seen, int code_commented,
                      int work_time);

        JobsForSprint(char **rows);
    };

    inline void to_json(nlohmann::json &j, const JobsForSprint &p) {
        j = nlohmann::json{
                {"personID",            p.personID},
                {"person",              p.person},
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

    inline void from_json(const nlohmann::json &j, JobsForSprint &p) {
        j.at("personID").get_to(p.personID);
        j.at("person").get_to(p.person);
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
