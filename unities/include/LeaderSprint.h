#pragma once
#include "SprintBase.h"

namespace unities {
    using namespace std;

    class LeaderSprint : public SprintBase {
    public:
        double SprintValue;
        LeaderSprint(int sprint_id, string n);
        LeaderSprint();
    };
}

