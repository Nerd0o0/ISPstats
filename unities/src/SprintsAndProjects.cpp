#include "../include/SprintsAndProjects.h"
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <nlohmann/json.hpp>

namespace unities {
    using namespace std;
        SprintsAndProjects::SprintsAndProjects(int sprint_id, string project_name, string sprint_name, string begin_s, string end_s, int bug_count,
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
        SprintsAndProjects::SprintsAndProjects(char **rows):SprintsAndProjects(stoi(rows[0]),rows[1],rows[2],rows[3],rows[4],stoi(rows[5]),
                                                           stoi(rows[6]),stoi(rows[7]),stoi(rows[8]),stoi(rows[9]),
                                                           stoi(rows[10]),stoi(rows[11]),stoi(rows[12]),stoi(rows[13]),stoi(rows[14]),stoi(rows[15])){}
}
