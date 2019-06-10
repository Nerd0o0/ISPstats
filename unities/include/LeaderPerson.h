#pragma once
#include "Base.h"

namespace unities {
    using namespace std;

    class LeaderPerson : public Base {
    public:
        double personValue;

        LeaderPerson(int person_id, std::string n, double value);

        LeaderPerson(char **rows);
    };

    inline void to_json(nlohmann::json &j, const LeaderPerson &p) {
        j = nlohmann::json{
                {"personID", p.id},
                {"name",     p.name},
                {"value",    p.personValue}

        };
    }
}