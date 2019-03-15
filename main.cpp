#include <iostream>
#include "database.h"

using namespace std;

int main(){
    Database db;
    db.start();
    db.printAllStr();
    return 0;
}