#include "../include/Base.h"
#include <string>

namespace unities {
    Base::Base(int _id, std::string n) : id(_id), name(n) {}

    Base::Base(char **rows) : Base(std::stoi(rows[0]), rows[1]) {}
    Base::Base(){}
}
