#include "../include/ProjectBase.h"
#include <nlohmann/json.hpp>
#include <string>

namespace unities {
    using namespace std;
        ProjectBase::ProjectBase(int project_id, std::string n) : projectID(project_id), name(n){}
        ProjectBase::ProjectBase(char **rows):ProjectBase(stoi(rows[0]),rows[1]){}
        ProjectBase::ProjectBase(){}
}

