#include <iostream>

#include "SymbolTable.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    SymbolTable mst;

    mst.AddEntry("X",CHEESE_LIT);
    mst.AddEntry("Y",BOOL_LIT);
    mst.AddEntry("A",FLOAT_LIT);
    mst.AddEntry("Z",INT_LIT);
    mst.AddEntry("B",INT_LIT);

    mst.UpdateEntry("X","Hello");
    mst.UpdateEntry("Y","false");
    mst.UpdateEntry("A","10.1");
    mst.UpdateEntry("Z","10");
    // mst.UpdateEntry("B","10.1");

    cout << mst.GetDataObject("X").GetValue() << " label name: " << mst.GetDataObject("X").GetDataLabel() << endl;
    cout << mst.GetDataObject("Y").GetValue() << " label name: " << mst.GetDataObject("Y").GetDataLabel() << endl;
    cout << mst.GetDataObject("Z").GetValue() << " label name: " << mst.GetDataObject("Z").GetDataLabel() << endl;

    cout << mst.FinishSymbolTable() << endl;

    return 0;
}