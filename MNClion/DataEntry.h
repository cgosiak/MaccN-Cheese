//
// Created by caleb on 4/6/16.string
//

#ifndef MNCLION_DATAENTRY_H
#define MNCLION_DATAENTRY_H

#include <string>

enum DataTypes  { TYPE_BOOL, TYPE_CHEESE, TYPE_INT, TYPE_FLOAT};

class DataEntry {

public:
    DataEntry(std::string id, DataTypes type); // initialization of entry

    // void AssignType(DataTypes type); // define the type of the object

    void AssignValue(std::string val); // assign a value to the variable

    DataTypes GetType(); // return the type of the object

    std::string GetValue(); // return a string representation of the value stored in this variable

    std::string GetID(); // return id of object

private:
    DataTypes entry_type; // the type of the variable

    bool entry_used = false; // Test of whether the variable was ever assigned a value

    // Name of variable
    std::string variable_name;

    // Value assigned to variable
    std::string value;

};


#endif //MNCLION_DATAENTRY_H
