#ifndef DATABASE_H
#define DATABASE_H

#include "Event.h"
#include <vector>
#include <string>

using namespace std;

class Database {
private:
    vector<Event> events;
    string filename;
    bool modified;

public:
    // Constructor
    Database(const string& file = "events.csv");

    // Event management
    void addEvent(const Event& event);
    bool updateEvent(size_t index, const Event& event);
    bool deleteEvent(size_t index);

    // Search functions
    vector<Event> searchByName(const string& query) const;
    vector<Event> searchByYear(int year) const;
    vector<Event> searchByYearRange(int startYear, int endYear) const;

    // Data access
    const vector<Event>& getAllEvents() const;
    size_t getEventCount() const;
    Event getEvent(size_t index) const;

    // File operations
    bool loadFromFile();
    bool saveToFile() const;
    bool isModified() const;

    // Sample data
    void addSampleData();
};

#endif // DATABASE_H