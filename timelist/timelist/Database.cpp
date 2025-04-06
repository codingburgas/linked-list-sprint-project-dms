#include "Database.h"
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

Database::Database(const string& file) : filename(file), modified(false) {}

void Database::addEvent(const Event& event) {
    events.push_back(event);
    modified = true;
}

bool Database::updateEvent(size_t index, const Event& event) {
    if (index < events.size()) {
        events[index] = event;
        modified = true;
        return true;
    }
    return false;
}

bool Database::deleteEvent(size_t index) {
    if (index < events.size()) {
        events.erase(events.begin() + index);
        modified = true;
        return true;
    }
    return false;
}

vector<Event> Database::searchByName(const string& query) const {
    vector<Event> results;
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (const auto& event : events) {
        string lowerName = event.getName();
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        if (lowerName.find(lowerQuery) != string::npos) {
            results.push_back(event);
        }
    }
    return results;
}

vector<Event> Database::searchByYear(int year) const {
    vector<Event> results;
    for (const auto& event : events) {
        if (event.getYear() == year) {
            results.push_back(event);
        }
    }
    return results;
}

vector<Event> Database::searchByYearRange(int startYear, int endYear) const {
    vector<Event> results;
    for (const auto& event : events) {
        int year = event.getYear();
        if (year >= startYear && year <= endYear) {
            results.push_back(event);
        }
    }
    return results;
}

const vector<Event>& Database::getAllEvents() const {
    return events;
}

size_t Database::getEventCount() const {
    return events.size();
}

Event Database::getEvent(size_t index) const {
    if (index < events.size()) {
        return events[index];
    }
    return Event(); // Return empty event if index is invalid
}

bool Database::loadFromFile() {
    events.clear();

    try {
        ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                Event event;
                event.fromString(line);
                events.push_back(event);
            }
        }

        file.close();
        modified = false;
        return true;
    }
    catch (const exception& e) {
        cerr << "Error loading from file: " << e.what() << endl;
        return false;
    }
}

bool Database::saveToFile() const {
    try {
        ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        for (const auto& event : events) {
            file << event.toString() << endl;
        }

        file.close();
        return true;
    }
    catch (const exception& e) {
        cerr << "Error saving to file: " << e.what() << endl;
        return false;
    }
}

bool Database::isModified() const {
    return modified;
}

void Database::addSampleData() {
    events.clear();

    addEvent(Event(0, "Birth of Jesus Christ", "Bethlehem", "Jesus, Mary, Joseph"));
    addEvent(Event(33, "Crucifixion of Jesus", "Jerusalem", "Jesus, Pontius Pilate"));
    addEvent(Event(476, "Fall of the Western Roman Empire", "Rome, Italy", "Romulus Augustus, Odoacer"));
    addEvent(Event(1066, "Battle of Hastings", "Hastings, England", "William the Conqueror, Harold Godwinson"));
    addEvent(Event(1215, "Magna Carta Signed", "Runnymede, England", "King John, English barons"));
    addEvent(Event(1492, "Columbus Reaches the Americas", "Bahamas", "Christopher Columbus"));
    addEvent(Event(1776, "United States Declaration of Independence", "Philadelphia, USA", "Thomas Jefferson, John Adams, Benjamin Franklin"));
    addEvent(Event(1789, "French Revolution Begins", "Paris, France", "Louis XVI, Marie Antoinette"));
    addEvent(Event(1914, "World War I Begins", "Europe", "Archduke Franz Ferdinand"));
    addEvent(Event(1945, "End of World War II", "Global", "Harry Truman, Adolf Hitler, Joseph Stalin"));
    addEvent(Event(1969, "First Moon Landing", "Moon", "Neil Armstrong, Buzz Aldrin"));
    addEvent(Event(1989, "Fall of the Berlin Wall", "Berlin, Germany", "Mikhail Gorbachev"));
    addEvent(Event(2001, "September 11 Attacks", "New York, USA", "Osama bin Laden"));
    addEvent(Event(2020, "COVID-19 Pandemic", "Global", "Various world leaders"));

    modified = true;
}