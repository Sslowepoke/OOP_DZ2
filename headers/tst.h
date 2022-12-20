#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

using namespace std;

// check if type is defined, forward declarations are not definitions
template <class, class = void>
struct is_defined : std::false_type {};
template <class T>
struct is_defined<
    T, std::enable_if_t<std::is_object<T>::value &&
                        !std::is_pointer<T>::value && (sizeof(T) > 0)>>
    : std::true_type {};

namespace Test1 {

template <class, class = void>
struct is_defined_method : std::false_type {};

template <class PhoneBook>
struct is_defined_method<
    PhoneBook,
    std::enable_if_t<
        std::is_same<decltype(std::declval<PhoneBook>().loadPhonebook(std::declval<string>())),
                     void>::value &&
        std::is_same<decltype(std::declval<PhoneBook>().openTerminal()), void>::value>>
    : std::true_type {};

template <class PhoneBook>
int tst() {
    if constexpr (is_defined<PhoneBook>::value &&
                  is_defined_method<PhoneBook>::value) {
        std::stringstream input;
        std::streambuf *cinbuf = std::cin.rdbuf(); // save old buffer
        std::cin.rdbuf(input.rdbuf()); // redirect std::cin stringstream!

        std::stringstream output;
        std::streambuf *coutbuf = std::cout.rdbuf(); // save old buffer
        std::cout.rdbuf(output.rdbuf()); // redirect std::cout stringstream!

        input << "SEARCH\n"
                 "Baja\n"
                 "exit\n";

        PhoneBook& pb = PhoneBook::getInstance();
        const string path = "tst.csv";
        pb.loadPhonebook(path);
        pb.openTerminal();

        const string correctOutput = "- 1 contacts have been found :\n"
                                     "-- - Bajaga 011 123456\n";

        // restore cin, cout
        std::cin.rdbuf(cinbuf);
        std::cout.rdbuf(coutbuf);

        if (output.str().find(correctOutput) != std::string::npos) {
            std::cout << "Test passed" << std::endl;
            return 0;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test1

namespace Test2 {

template <class, class = void>
struct is_defined_method : std::false_type {};

template <class PhoneBook>
struct is_defined_method<
    PhoneBook,
    std::enable_if_t<
        std::is_same<decltype(std::declval<PhoneBook>().loadPhonebook(std::declval<string>())),
                     void>::value &&
        std::is_same<decltype(std::declval<PhoneBook>().openTerminal()), void>::value>>
    : std::true_type {};

template <class PhoneBook>
int tst() {
    if constexpr (is_defined<PhoneBook>::value &&
                  is_defined_method<PhoneBook>::value) {
        std::stringstream input;
        std::streambuf *cinbuf = std::cin.rdbuf(); // save old buffer
        std::cin.rdbuf(input.rdbuf()); // redirect std::cin stringstream!

        std::stringstream output;
        std::streambuf *coutbuf = std::cout.rdbuf(); // save old buffer
        std::cout.rdbuf(output.rdbuf()); // redirect std::cout stringstream!

        input << "SELECT\n"
                 "Bajaga\n"
                 "exit\n";

        PhoneBook& pb = PhoneBook::getInstance();
        const string path = "tst.csv";
        pb.loadPhonebook(path);
        pb.openTerminal();

        const string correctOutput =
            "- Contact Bajaga 011 123456 is now selected.";

        // restore cin, cout
        std::cin.rdbuf(cinbuf);
        std::cout.rdbuf(coutbuf);

        if (output.str().find(correctOutput) != std::string::npos) {
            std::cout << "Test passed" << std::endl;
            return 0;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test2

namespace Test3 {

template <class, class = void>
struct is_defined_method : std::false_type {};

template <class PhoneBook>
struct is_defined_method<
    PhoneBook,
    std::enable_if_t<
        std::is_same<decltype(std::declval<PhoneBook>().loadPhonebook(std::declval<string>())),
                     void>::value &&
        std::is_same<decltype(std::declval<PhoneBook>().openTerminal()), void>::value>>
    : std::true_type {};

template <class PhoneBook>
int tst() {
    if constexpr (is_defined<PhoneBook>::value &&
                  is_defined_method<PhoneBook>::value) {
        std::stringstream input;
        std::streambuf *cinbuf = std::cin.rdbuf(); // save old buffer
        std::cin.rdbuf(input.rdbuf()); // redirect std::cin stringstream!

        std::stringstream output;
        std::streambuf *coutbuf = std::cout.rdbuf(); // save old buffer
        std::cout.rdbuf(output.rdbuf()); // redirect std::cout stringstream!

        input << "SELECT\n"
                 "Bajaga\n"
                 "CALL\n"
                 "CALL_HISTORY\n"
                 "exit\n";

        PhoneBook& pb = PhoneBook::getInstance();
        const string path = "tst.csv";
        pb.loadPhonebook(path);
        pb.openTerminal();

        const string correctOutput1 =
            "- Contact Bajaga 011 123456 is now selected.";

        const string correctOutput2 = "-- Bajaga 011 123456";

        // restore cin, cout
        std::cin.rdbuf(cinbuf);
        std::cout.rdbuf(coutbuf);

        if (output.str().find(correctOutput1) != std::string::npos &&
            output.str().find(correctOutput2) != std::string::npos) {
            std::cout << "Test passed" << std::endl;
            return 0;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test3

namespace Test4 {

template <class, class = void>
struct is_defined_method : std::false_type {};

template <class PhoneBook>
struct is_defined_method<
    PhoneBook,
    std::enable_if_t<
        std::is_same<decltype(std::declval<PhoneBook>().loadPhonebook(std::declval<string>())),
                     void>::value &&
        std::is_same<decltype(std::declval<PhoneBook>().openTerminal()), void>::value>>
    : std::true_type {};

template <class PhoneBook>
int tst() {
    if constexpr (is_defined<PhoneBook>::value &&
                  is_defined_method<PhoneBook>::value) {
        std::stringstream input;
        std::streambuf *cinbuf = std::cin.rdbuf(); // save old buffer
        std::cin.rdbuf(input.rdbuf()); // redirect std::cin stringstream!

        std::stringstream output;
        std::streambuf *coutbuf = std::cout.rdbuf(); // save old buffer
        std::cout.rdbuf(output.rdbuf()); // redirect std::cout stringstream!

        // edit name, name == 1
        input << "SELECT\n"
                 "Bajaga\n"
                 "EDIT\n"
                 "1\n"
                 "Momcilo Bajagic\n"
                 "exit\n";

        PhoneBook& pb = PhoneBook::getInstance();
        const string path = "tst.csv";
        pb.loadPhonebook(path);
        pb.openTerminal();

        const string correctOutput1 =
            "- Contact Bajaga 011 123456 is now selected.";

        const string correctOutput2 = "-- Momcilo Bajagic 011 123456";

        // restore cin, cout
        std::cin.rdbuf(cinbuf);
        std::cout.rdbuf(coutbuf);

        if (output.str().find(correctOutput1) != std::string::npos &&
            output.str().find(correctOutput2) != std::string::npos) {
            std::cout << "Test passed" << std::endl;
            return 0;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test4