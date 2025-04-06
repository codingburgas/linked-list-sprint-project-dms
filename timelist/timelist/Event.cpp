#include "Event.h"
#include <sstream>
#include <vector>

using namespace std;

// Default constructor
Event::Event() : year(0), name(""), location(""), keyFigures("") {}

// Parameterized constructor
Event::Event(int y, const string& n, const string& l, const string& k)
    : year(y), name(n), location(l), keyFigures(k) {}

// Getters
int Event::getYear() const { return year; }
string Event::getName() const { return name; }
string Event::getLocation() const { return location; }
string Event::getKeyFigures() const { return keyFigures; }

// Setters
void Event::setYear(int y) { year = y; }
void Event::setName(const string& n) { name = n; }
void Event::setLocation(const string& l) { location = l; }
void Event::setKeyFigures(const string& k) { keyFigures = k; }

// Convert event to string (CSV format)
string Event::toString() const {
    stringstream ss;
    // Use pipe as delimiter to handle commas in text fields
    ss << year << "|" << name << "|" << location << "|" << keyFigures;
    return ss.str();
}

// Parse event from string (CSV format)
void Event::fromString(const string& str) {
    stringstream ss(str);
    string token;
    vector<string> tokens;

    // Split by pipe delimiter
    while (getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    if (tokens.size() >= 4) {
        try {
            year = stoi(tokens[0]);
            name = tokens[1];
            location = tokens[2];
            keyFigures = tokens[3];
        }
        catch (const exception& e) {
            // Handle parsing errors
            year = 0;
            name = "Error parsing event";
            location = "";
            keyFigures = "";
        }
    }
}