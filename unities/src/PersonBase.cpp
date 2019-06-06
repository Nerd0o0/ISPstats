#include "../include/PersonBase.h"
#include <nlohmann/json.hpp>
#include <string>

namespace unities {
    using namespace std;
        PersonBase::PersonBase(int person_id, std::string n) : personID(person_id), name(n){}
        PersonBase::PersonBase(char **rows):PersonBase(stoi(rows[0]),rows[1]){}
        PersonBase::PersonBase(){}
}

