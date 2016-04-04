//
// Created by gosi1cal on 4/4/16.
//

#ifndef FINAL_COMPILER_SYMBOLTABLE_H
#define FINAL_COMPILER_SYMBOLTABLE_H

enum DataTypes  { TYPE_BOOL, TYPE_CHEESE, TYPE_INT, TYPE_FLOAT};

class SymbolTable {

public:
    SymbolTable(); // Initializes Symbol Table Object

    void AddEntry(); // Add entry to symbol table

private:
    int TableEntries;

};


#endif //FINAL_COMPILER_SYMBOLTABLE_H
