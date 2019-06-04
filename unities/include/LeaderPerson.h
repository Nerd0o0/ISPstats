#pragma once
#include "PersonBase.h"
#include <iostream>

namespace unities {
    using namespace std;

    class LeaderPerson : public PersonBase {
    public:
        double personValue;

        LeaderPerson(int person_id, std::string n, double value) : PersonBase(person_id,n), personValue(value) {}

        LeaderPerson(char **rows) : LeaderPerson(stoi(rows[0]),rows[1],stod(rows[2])){}
    };

    inline void to_json(nlohmann::json &j, const LeaderPerson &p) {
        j = nlohmann::json{
                {"personID", p.personID},
                {"name",     p.name},
                {"value",    p.personValue}

        };
    }
}