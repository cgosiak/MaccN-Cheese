#include <iostream>

#include "SymbolTable.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    SymbolTable mst;

    mst.AddEntry("X",TYPE_CHEESE);
    mst.AddEntry("Y",TYPE_CHEESE);
    mst.AddEntry("Z",TYPE_CHEESE);

    mst.UpdateEntry("X","Hello");
    mst.UpdateEntry("Y","World");
    mst.UpdateEntry("Z","Caleb");

    cout << mst.GetDataObject("X").GetValue() << endl;
    cout << mst.GetDataObject("Y").GetValue() << endl;
    cout << mst.GetDataObject("Z").GetValue() << endl;

    return 0;
}