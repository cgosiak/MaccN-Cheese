#include <iostream>

#include "SymbolTable.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    SymbolTable mst;

    mst.AddEntry("X",TYPE_CHEESE);
    mst.AddEntry("Y",TYPE_BOOL);
    mst.AddEntry("A",TYPE_BOOL);
    mst.AddEntry("Z",TYPE_INT);
    mst.AddEntry("B",TYPE_INT);

    mst.UpdateEntry("X","Hello");
    mst.UpdateEntry("Y","false");
    mst.UpdateEntry("A","caleb");
    mst.UpdateEntry("Z","10");
    mst.UpdateEntry("B","10.1");

    cout << mst.GetDataObject("X").GetValue() << endl;
    cout << mst.GetDataObject("Y").GetValue() << endl;
    cout << mst.GetDataObject("Z").GetValue() << endl;

    return 0;
}