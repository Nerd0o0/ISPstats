#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace unities {
    using namespace std;
    class PersonBase {
    public:
        int personID;
        std::string name;
        PersonBase(int person_id, std::string n);
        PersonBase(char **rows);
        PersonBase();
    };
    inline void to_json(nlohmann::json &j, const PersonBase &p) {
        j = nlohmann::json{
                {"personID",  p.personID},
                {"name",      p.name}
        };
    }

    inline void from_json(const nlohmann::json &j, PersonBase &p){
        j.at("personID").get_to(p.personID);
        j.at("name").get_to(p.name);
    }
}

