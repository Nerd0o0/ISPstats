#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace unities {
    using namespace std;
    class ProjectBase {
    public:
        int projectID;
        std::string name;
        ProjectBase(int project_id, std::string n);
        ProjectBase(char **rows);
        ProjectBase(){}
    };
    inline void to_json(nlohmann::json &j, const ProjectBase &p) {
        j = nlohmann::json{
                {"projectID", p.projectID},
                {"name",      p.name}
        };
    }

    inline void from_json(const nlohmann::json &j, ProjectBase &p){
        j.at("projectID").get_to(p.projectID);
        j.at("name").get_to(p.name);
    }
}

