#include "Number.h"
#include <sstream>
#include "PhonebookException.h"


Number* Number::makeNumber(const std::string& number_string) {
    if(number_string[0] == '0') { //starts with 0
        if(number_string[1] == '1' && number_string[2] == '1') {
            if(number_string.length() - 4 > max_number_length) throw number_too_long();
            return new HomeNumber("0", number_string.substr(4, max_number_length));
        }
        else if(number_string[1] == '6') {
            if(number_string.length() - 4 > max_number_length) throw number_too_long();
            return new MobileNumber("0", number_string.substr(1,2), number_string.substr(4, max_number_length));
        }
        else {
            throw invalid_number_format(number_string);
        }
    }
    else { //starts with +381
        if(number_string.find("+381") == std::string::npos) {
            throw invalid_number_format(number_string);
        }
        if(number_string[5] == '1' && number_string[6] == '1') {
            if(number_string.length() - 8 > max_number_length) throw number_too_long();
            return new HomeNumber("+381", number_string.substr(8, max_number_length));
        }
        else if(number_string[5] == '6') {
            if(number_string.length() - 8 > max_number_length) throw number_too_long();
            return new MobileNumber("+381", number_string.substr(5, 2), number_string.substr(8, max_number_length));
        }        
        else {
            throw invalid_number_format(number_string);
            // return nullptr;
        }
    }
}


std::ostream& operator<<(std::ostream& os, Number* number) {
    return number->print(os);
}

//MobileNumber
std::ostream& MobileNumber::print(std::ostream& os) const{
    if(prefix == "0") {
        return os << prefix << call_number << " " << number << " ";
    }
    else
        return os << prefix << " " << call_number << " " << number << " ";
}

Number* MobileNumber::makeCopy() {
    return new MobileNumber(*this);
}



//HomeNumber
std::string HomeNumber::call_number = "11";

std::ostream& HomeNumber::print(std::ostream& os) const{
    if(prefix == "0") {
        return os << prefix << call_number << " " << number << " ";
    }
    else
        return os << prefix << " " << call_number << " " << number << " ";
}

Number* HomeNumber::makeCopy() {
    return new HomeNumber(*this);
}
 