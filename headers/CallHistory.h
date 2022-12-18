#pragma once

#include <list>
using std::list;
#include <chrono>
#include <ctime>

#include "Contact.h"


class Call {
public:
    Call(Contact* contact) : contact(contact), time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {}
    friend std::ostream& operator<<(std::ostream& os, const Call& call);

private:
    Contact* contact;
    std::time_t time;

};

class CallHistory {
public:
    CallHistory();
    void call(Contact* contact);
    friend std::ostream& operator<<(std::ostream& os, const CallHistory& call_history);
private:
    static constexpr int call_history_length = 2;
    list<Call> call_list;
};
