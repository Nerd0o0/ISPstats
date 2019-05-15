#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <nlohmann/json.hpp>

namespace unities {
    using namespace std;
    class SprintsAndProjects {
    public:
        int sprintID;
        string project;
        std::string sprint;
        boost::gregorian::date sprintBegin;
        boost::gregorian::date sprintEnd;
        int bugCount;
        int estimationBugTime;
        int completeBugCount;
        int completeBugEstimation;
        int completeBugFact;
        int incompleteBugCount;
        int incompleteBugEstimation;
        int incompleteBugFact;
        int codeBranches;
        int codeDiscussion;
        int codeReturns;

        SprintsAndProjects(int sprint_id, string project_name, string sprint_name, string begin_s, string end_s, int bug_count,
               int estimation_bug_time, int complete_bug_count, int complete_bug_estimation, int complete_bug_fact,
               int incomplete_bug_count, int incomplete_bug_estimation, int incomplete_bug_fact, int code_branches,
               int code_discussion, int code_returns) :
                sprintID(sprint_id), project(project_name), sprint(sprint_name),
                sprintBegin(boost::gregorian::from_string(begin_s)),
                sprintEnd(boost::gregorian::from_string(end_s)), bugCount(bug_count),
                estimationBugTime(estimation_bug_time), completeBugCount(complete_bug_count),
                completeBugEstimation(complete_bug_estimation), completeBugFact(complete_bug_fact),
                incompleteBugCount(incomplete_bug_count), incompleteBugEstimation(incomplete_bug_estimation),
                incompleteBugFact(incomplete_bug_fact), codeBranches(code_branches), codeDiscussion(code_discussion),
                codeReturns(code_returns) {}
        SprintsAndProjects(char **rows):SprintsAndProjects(stoi(rows[0]),rows[1],rows[2],rows[3],rows[4],stoi(rows[5]),
                stoi(rows[6]),stoi(rows[7]),stoi(rows[8]),stoi(rows[9]),
                stoi(rows[10]),stoi(rows[11]),stoi(rows[12]),stoi(rows[13]),stoi(rows[14]),stoi(rows[15])){}
        SprintsAndProjects(){}

    };

    inline void to_json(nlohmann::json &j, const SprintsAndProjects &p) {
        j = nlohmann::json{
                {"sprintID",                p.sprintID},
                {"project",                 p.project},
                {"sprint",                  p.sprint},
                {"sprintBegin",             boost::gregorian::to_simple_string(p.sprintBegin)},
                {"sprintEnd",               boost::gregorian::to_simple_string(p.sprintEnd)},
                {"bugCount",                p.bugCount},
                {"estimationBugTime",       p.estimationBugTime},
                {"completeBugCount",        p.completeBugCount},
                {"completeBugEstimation",   p.completeBugEstimation},
                {"completeBugFact",         p.completeBugFact},
                {"incompleteBugCount",      p.incompleteBugCount},
                {"incompleteBugEstimation", p.incompleteBugEstimation},
                {"incompleteBugFact",       p.incompleteBugFact},
                {"codeBranches",            p.codeBranches},
                {"codeDiscussion",          p.codeDiscussion},
                {"codeReturns",             p.codeReturns}

        };
    }

    inline void from_json(const nlohmann::json &j, SprintsAndProjects &p) {
        j.at("sprintID").get_to(p.sprintID);
        j.at("project").get_to(p.project);
        j.at("sprint").get_to(p.sprint);
        std::string begin;
        std::string end;
        j.at("sprintBegin").get_to(begin);
        j.at("sprintEnd").get_to(end);
        p.sprintBegin = boost::gregorian::from_string(begin);
        p.sprintEnd = boost::gregorian::from_string(end);
        j.at("bugCount").get_to(p.bugCount);
        j.at("estimationBugTime").get_to(p.estimationBugTime);
        j.at("completeBugCount").get_to(p.completeBugCount);
        j.at("completeBugEstimation").get_to(p.completeBugEstimation);
        j.at("completeBugFact").get_to(p.completeBugFact);
        j.at("incompleteBugCount").get_to(p.incompleteBugCount);
        j.at("incompleteBugEstimation").get_to(p.incompleteBugEstimation);
        j.at("incompleteBugFact").get_to(p.incompleteBugFact);
        j.at("codeBranches").get_to(p.codeBranches);
        j.at("codeDiscussion").get_to(p.codeDiscussion);
        j.at("codeReturns").get_to(p.codeReturns);
    }
}
