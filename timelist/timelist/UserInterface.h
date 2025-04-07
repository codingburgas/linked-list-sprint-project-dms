#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "Database.h"
#include <string>

using namespace std;

class UserInterface {
private:
    Database& db;

    // Menu functions
    void displayMainMenu() const;
    void viewAllEvents() const;
    void searchByName() const;
    void searchByYear() const;
    void searchByYearRange() const;
    void addNewEvent();
    void modifyEvent();
    void deleteEvent();
    void loadDatabase();
    void saveDatabase() const;

    // Helper functions
    void displayEvent(const Event& event, size_t index) const;
    void displayEvents(const vector<Event>& events) const;
    int getIntInput(const string& prompt) const;
    string getStringInput(const string& prompt) const;
    void clearScreen() const;
    void waitForKey() const;

public:
    UserInterface(Database& database);
    void run();
};

#endif // USER_INTERFACE_H