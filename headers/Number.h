#pragma once

#include <string>
#include <iostream>

class Number {
public:
    virtual ~Number() {}
    static Number* makeNumber(const std::string& number_string);
    virtual Number* makeCopy() = 0;
    static constexpr int max_number_length  = 12;
    virtual std::ostream& print(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, Number* number);
private:

};

class MobileNumber : public Number {
public:
    MobileNumber(const std::string& prefix, const std::string& call_number, const std::string& number):
    prefix(prefix), call_number(call_number), number(number) {}
    // MobileNumber(const MobileNumber& mobile_number):
    // prefix(mobile_number.prefix), call_number(mobile_number.call_number), number(mobile_number.number) {}
    ~MobileNumber() override {}
    std::ostream& print(std::ostream& os) const override;
    Number* makeCopy() override;

private:
    std::string prefix;
    std::string call_number;
    std::string number;
};

class HomeNumber : public Number {
public:
    HomeNumber(const std::string& prefix, const std::string& number):
    prefix(prefix), number(number) {}
    // HomeNumber(const HomeNumber& home_number);
    ~HomeNumber() override {}
    std::ostream& print(std::ostream& os) const override;
    Number* makeCopy() override;

private:
    std::string prefix;
    std::string number;
    static std::string call_number;


};