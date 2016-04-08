//
// Created by caleb on 4/6/16.
//

#include <iostream>
#include "DataEntry.h"
#include <algorithm>

DataEntry::DataEntry(std::string id, DataTypes type) {
    variable_name = id;
    entry_type = type;
}

void DataEntry::AssignValue(std::string val) {

    // Need to have case statement here to make sure assignment matches type
    switch (entry_type) {
        case TYPE_INT:
            if (DataEntry::isInt(val)) {
                value = val;
            }
            else {
                DataEntry::RaiseError_Assignment(val, "TYPE_INT");
            }
            break;
        case TYPE_BOOL:
            if (DataEntry::isBool(val)) {
                value = DataEntry::UpperCase(val);
            }
            else {
                DataEntry::RaiseError_Assignment(val, "TYPE_BOOL");
            }
            break;
        case TYPE_CHEESE:
            // should technically never be an error, any grouping of characters can be viewed as a string
            //DataEntry::RaiseError_Assignment(val, TYPE_CHEESE);
            value = val;
            break;
        case TYPE_FLOAT:
            DataEntry::RaiseError_Assignment(val, "TYPE_FLOAT");
            break;
        default:
            DataEntry::RaiseError_Assignment(val, "TYPE_NONE");
            break;
    }
}

DataTypes DataEntry::GetType() {
    return entry_type;
}

std::string DataEntry::GetValue() {
    return value;
}

std::string DataEntry::GetID() {
    return variable_name;
}

void DataEntry::RaiseError_Assignment(std::string in, std::string t) {
    std::cout << "Assignment Error: Cannot assign value " << in << " to type " << t << std::endl;
}

bool DataEntry::isInt(const std::string &s) {
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

    char * p ;
    strtol(s.c_str(), &p, 10) ;

    return (*p == 0) ;
}

bool DataEntry::isBool(const std::string &s) {
    std::string uc = DataEntry::UpperCase(s);
    if (uc == "FALSE" || uc == "TRUE") {
        return true;
    }
    else {
        return false;
    }
}

std::string DataEntry::UpperCase(std::string sr) {
    std::string s = sr;
    for (auto & c: s) c = toupper(c);

    return s;
}
