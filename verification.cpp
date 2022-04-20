#include "functions.h"

// functions to compare students for sorting

bool compareByName(const data& a, const data& b) {
    if (a.name != b.name)
        return a.name < b.name;
    else
        return a.surname < b.surname;
}

bool compareBySurname(const data& a, const data& b) {
    if (a.surname != b.surname)
        return a.surname < b.surname;
    else
        return a.name < b.name;
}

// functions to check if input is correct

bool is_grade(string s) {
    // if string contains characters from 0 to 9 or is equal to 10 return true
    std::regex reg("[0-9]");
    if (std::regex_match(s, reg) || s == "10")
        return true;
    else
        return false;
}

bool is_int(string s) {
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

bool check_name(string s) {
    // if string starts with capital letter and contains only letters return true
    std::regex reg("^[A-Z][a-z]*$");
    if (std::regex_match(s, reg))
        return true;
    else
        return false;
}

bool check_select(string s) {
    // if string is equal either to 1 or 2 return true
    std::regex reg("[1-2]");
    if (std::regex_match(s, reg))
        return true;
    else
        return false;
}

bool check_select1(string s) {
    // if string is equal either to 1 or 2 return true
    std::regex reg("[1-3]");
    if (std::regex_match(s, reg))
        return true;
    else
        return false;
}