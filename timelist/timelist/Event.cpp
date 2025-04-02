#include "Event.h"
#include <algorithm>


Event::Event(int y, int m, const std::string& t, const std::string& top,
    const std::string& loc, const std::string& lead,
    const std::vector<std::string>& part, const std::string& res)
    : year(y), month(m), title(t), topic(top), location(loc),
    leader(lead), participants(part), result(res) {

    if (month < 0 || month > 12) {
        month = 0;
    }
}


int Event::getYear() const { return year; }
int Event::getMonth() const { return month; }
std::string Event::getTitle() const { return title; }
std::string Event::getTopic() const { return topic; }
std::string Event::getLocation() const { return location; }
std::string Event::getLeader() const { return leader; }
std::vector<std::string> Event::getParticipants() const { return participants; }
std::string Event::getResult() const { return result; }


void Event::setYear(int y) { year = y; }
void Event::setMonth(int m) { month = (m >= 0 && m <= 12) ? m : 0; }
void Event::setTitle(const std::string& t) { title = t; }
void Event::setTopic(const std::string& t) { topic = t; }
void Event::setLocation(const std::string& l) { location = l; }
void Event::setLeader(const std::string& l) { leader = l; }
void Event::setParticipants(const std::vector<std::string>& p) { participants = p; }
void Event::setResult(const std::string& r) { result = r; }


void Event::display(bool compact) const {
    if (compact) {
        std::cout << getDateString() << " - " << title << " (" << topic << ")\n";
    }
    else {
        std::cout << "\n=== Event Details ===\n";
        std::cout << "Title: " << title << "\n";
        std::cout << "Date: " << getDateString() << "\n";
        std::cout << "Topic: " << topic << "\n";
        std::cout << "Location: " << location << "\n";
        std::cout << "Leader: " << leader << "\n";

        std::cout << "Participants: ";
        if (participants.empty()) {
            std::cout << "None";
        }
        else {
            for (size_t i = 0; i < participants.size(); ++i) {
                if (i != 0) std::cout << ", ";
                std::cout << participants[i];
            }
        }
        std::cout << "\nResult: " << result << "\n";
    }
}


bool Event::operator<(const Event& other) const {
    if (year != other.year) return year < other.year;
    return month < other.month;
}

bool Event::operator>(const Event& other) const {
    if (year != other.year) return year > other.year;
    return month > other.month;
}

bool Event::operator==(const Event& other) const {
    return year == other.year && month == other.month;
}


std::string Event::getDateString() const {
    if (month == 0) {
        return std::to_string(year);
    }
    return std::to_string(month) + "/" + std::to_string(year);
}