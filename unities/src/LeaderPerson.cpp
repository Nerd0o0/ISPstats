#include "../include/LeaderPerson.h"
namespace unities {
    LeaderPerson::LeaderPerson(int person_id, std::string n, double value) : PersonBase(person_id, n), personValue(value) {}
    
    LeaderPerson::LeaderPerson(char **rows) : LeaderPerson(stoi(rows[0]), rows[1], stod(rows[2])) {}
}