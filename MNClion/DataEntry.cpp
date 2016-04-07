//
// Created by caleb on 4/6/16.
//

#include "DataEntry.h"

DataEntry::DataEntry(std::string id, DataTypes type) {
    variable_name = id;
    entry_type = type;
}

void DataEntry::AssignValue(std::string val) {
    value = val;
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
