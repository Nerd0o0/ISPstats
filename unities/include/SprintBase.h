#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace unities {
    using namespace std;
    class SprintBase : Base{
    public:
        int sprintID;
        std::string name;

        SprintBase(int sprint_id, std::string n);
        SprintBase(char **rows);
        SprintBase();

    };

    inline void to_json(nlohmann::json &j, const SprintBase &p) {
        j = nlohmann::json{
                {"sprintID",                p.sprintID},
                {"name",                    p.name},

        };
    }

    inline void from_json(const nlohmann::json &j, SprintBase &p) {
        j.at("sprintID").get_to(p.sprintID);
        j.at("name").get_to(p.name);
    }
}
