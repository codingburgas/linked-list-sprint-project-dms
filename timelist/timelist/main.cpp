#include "Database.h"
#include "UserInterface.h"
#include <iostream>

using namespace std;

int main() {
    try {
        // Create database with default filename
        Database db("events.csv");

        // Create and run user interface
        UserInterface ui(db);
        ui.run();
    }
    catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }

    return 0;
}