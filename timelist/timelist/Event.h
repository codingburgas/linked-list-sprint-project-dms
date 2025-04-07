#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;

class Event {
private:
    int year;
    string name;
    string location;
    string keyFigures;

public:
    // Constructors
    Event();
    Event(int y, const string& n, const string& l, const string& k);

    // Getters
    int getYear() const;
    string getName() const;
    string getLocation() const;
    string getKeyFigures() const;

    // Setters
    void setYear(int y);
    void setName(const string& n);
    void setLocation(const string& l);
    void setKeyFigures(const string& k);

    // Utility methods
    string toString() const;
    void fromString(const string& str);
};

#endif // EVENT_H