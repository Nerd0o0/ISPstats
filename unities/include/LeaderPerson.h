#pragma once
#include "PersonBase.h"

namespace unities {
    using namespace std;

    class LeaderPerson : public PersonBase {
    public:
        double personValue;

        LeaderPerson(int person_id, std::string n, double value);

        LeaderPerson(char **rows);
    };

    inline void to_json(nlohmann::json &j, const LeaderPerson &p) {
        j = nlohmann::json{
                {"personID", p.personID},
                {"name",     p.name},
                {"value",    p.personValue}

        };
    }
}