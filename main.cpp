#include <iostream>
#include "database.h"

using namespace std;

int main(){
    Database db;
    db.start();
    db.narrow(5, 0, "");
    db.printAllStr();
    return 0;
}