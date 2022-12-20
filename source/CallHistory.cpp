#include "CallHistory.h"

void CallHistory::call(Contact* contact) {
    call_list.push_front(new Call(contact));
    if(call_list.size() > call_history_length) {
    call_list.pop_back();
    }
    std::cout << "- You just called " << (*contact) << std::endl;
}

std::ostream& operator<<(std::ostream& os, const CallHistory& call_history) {
    std::cout << "- This is your call history: " << std::endl;
    for(auto call : call_history.call_list) {
        os << "-- " << (*call);
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Call& call) {
    if(call.contact)
        return os << *call.contact << " " << std::ctime(&call.time);
    else
        return os << call.number << " " << std::ctime(&call.time);
}

Call::Call(Contact* contact) :
contact(contact), time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())) {
    number = contact->getNumber()->makeCopy();
}

Call::~Call() {
    delete number;
}

CallHistory::~CallHistory() {
    clear();
}

void CallHistory::clear() {
    for (auto call : call_list) {
        delete call;
    }
}

void CallHistory::deletedContact(Contact* contact) {
    for(auto call : call_list) {
        call->deletedContact(contact);
    }
}

void Call::deletedContact(Contact* contact) {
    if(this->contact == contact) {
        this->contact = nullptr;
    }
}
