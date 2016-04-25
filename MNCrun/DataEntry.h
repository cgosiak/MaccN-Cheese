//
// Created by caleb on 4/6/16.string
//

#ifndef MNCLION_DATAENTRY_H
#define MNCLION_DATAENTRY_H

#include <string>

// TODO: Update these data types!!!! BOOL_LIT.....
enum DataTypes  { TYPE_BOOL, TYPE_CHEESE, TYPE_INT, TYPE_FLOAT, TYPE_NONE};

class DataEntry {

public:
    DataEntry(std::string id, DataTypes type, std::string label_name); // initialization of entry

    // void AssignType(DataTypes type); // define the type of the object

    void AssignValue(std::string val); // assign a value to the variable

    DataTypes GetType(); // return the type of the object

    std::string GetValue(); // return a string representation of the value stored in this variable

    std::string GetID(); // return id of object

    std::string GetDataLabel(); // return label name for assembly file

private:
    DataTypes entry_type; // the type of the variable

    bool entry_used = false; // Test of whether the variable was ever assigned a value

    // Name of variable
    std::string variable_name;

    // Name in data section of assembly language
    std::string label_value;

    // Value assigned to variable
    std::string value;

    // Some type checking
    bool isInt(const std::string & s); // checks if the string passed is of type int

    bool isBool(const std::string & s); // checks if the string passed is a valid bool

    // Type conversion
    std::string UpperCase(std::string s); // upper cases a string, returns upper cased string

    // Some error raising
    void RaiseError_Assignment(std::string in, std::string t); // assignment error

};


#endif //MNCLION_DATAENTRY_H
