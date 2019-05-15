#include "../include/SprintBase.h"
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <nlohmann/json.hpp>

namespace unities {
    using namespace std;
        SprintBase::SprintBase(int sprint_id, std::string n):sprintID(sprint_id), name(n){}
        SprintBase::SprintBase(char **rows):SprintBase(stoi(rows[0]),rows[1]){}
}
