#include "../include/JobsForSprint.h"
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <nlohmann/json.hpp>

namespace unities {
    using namespace std;

    JobsForSprint::JobsForSprint(int person_id, string person_name, int complete_count, int complete_est_time,
                                 int complete_fact_time,
                                 int incomplete_count, int incomplete_est_time, int incomplete_fact_time,
                                 int complete_help_time,
                                 int complete_help_count, int incomplete_help_time, int incomplete_help_count,
                                 int code_returns,
                                 int code_discussion, int code_branches, int code_merged, int code_seen,
                                 int code_commented, int work_time) :
            personID(person_id), person(person_name), completeCount(complete_count),
            completeEstTime(complete_est_time), completeFactTime(complete_fact_time),
            incompleteCount(incomplete_count), incompleteEstTime(incomplete_est_time),
            incompleteFactTime(incomplete_fact_time), completeHelpTime(complete_help_time),
            completeHelpCount(complete_help_count), incompleteHelpTime(incomplete_help_time),
            incompleteHelpCount(incomplete_help_count), codeReturns(code_returns), codeDiscussion(code_discussion),
            codeBranches(code_branches), codeMerged(code_merged), codeSeen(code_seen),
            codeCommented(code_commented), workTime(work_time) {}

    JobsForSprint::JobsForSprint(char **rows) : JobsForSprint(stoi(rows[0]), rows[1], stoi(rows[2]), stoi(rows[3]),
                                                              stoi(rows[4]),
                                                              stoi(rows[5]), stoi(rows[6]), stoi(rows[7]),
                                                              stoi(rows[8]),
                                                              stoi(rows[9]), stoi(rows[10]), stoi(rows[11]),
                                                              stoi(rows[12]),
                                                              stoi(rows[13]), stoi(rows[14]), stoi(rows[15]),
                                                              stoi(rows[16]), stoi(rows[17]),
                                                              (rows[18] == NULL) ? 0 : stoi(rows[18])) {}


}
