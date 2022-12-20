#pragma once

#include <list>
using std::list;
#include <chrono>
#include <ctime>

#include "Contact.h"


class Call {
public:
    Call(Contact* contact);
    friend std::ostream& operator<<(std::ostream& os, const Call& call);
    ~Call();
    void deletedContact(Contact* contact);

private:
    Contact* contact;
    Number* number;
    std::time_t time;

};

class CallHistory {
public:
    ~CallHistory();
    void call(Contact* contact);
    friend std::ostream& operator<<(std::ostream& os, const CallHistory& call_history);
    void clear();
    void deletedContact(Contact* contact);
private:
    static constexpr int call_history_length = 10;
    list<Call*> call_list;
};
