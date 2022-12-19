#include "CallHistory.h"


CallHistory::CallHistory() : call_list() {}


void CallHistory::call(Contact* contact) {
    call_list.push_front(Call(contact));
    if(call_list.size() > call_history_length) {
        call_list.pop_back();
    }
    std::cout << "- You just called " << (*contact) << std::endl;
}

std::ostream& operator<<(std::ostream& os, const CallHistory& call_history) {
    std::cout << "- This is your call history: " << std::endl;
    for(auto call : call_history.call_list) {
        os << "-- " << call;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Call& call) {
    return os << call.contact << " " << std::ctime(&call.time);
}