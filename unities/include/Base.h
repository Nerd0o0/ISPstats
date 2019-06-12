#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace unities {
    class Base {
    public:
        int id;
        std::string name;
        Base(int person_id, std::string n);
        Base(char **rows);
        Base();
    };
    inline void to_json(nlohmann::json &j, const Base &p) {
        j = nlohmann::json{
                {"id",  p.id},
                {"name",      p.name}
        };
    }

    inline void from_json(const nlohmann::json &j, Base &p){
        j.at("id").get_to(p.id);
        j.at("name").get_to(p.name);
    }
}

