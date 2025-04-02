#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <iostream>

class Event {
private:
    int year;                         
    int month;                       
    std::string title;              
    std::string topic;               
    std::string location;            
    std::string leader;              
    std::vector<std::string> participants; 
    std::string result;              

public:

    Event(int y, int m = 0,
        const std::string& t = "",
        const std::string& top = "",
        const std::string& loc = "",
        const std::string& lead = "",
        const std::vector<std::string>& part = {},
        const std::string& res = "");


    int getYear() const;
    int getMonth() const;
    std::string getTitle() const;
    std::string getTopic() const;
    std::string getLocation() const;
    std::string getLeader() const;
    std::vector<std::string> getParticipants() const;
    std::string getResult() const;

 
    void setYear(int y);
    void setMonth(int m);
    void setTitle(const std::string& t);
    void setTopic(const std::string& t);
    void setLocation(const std::string& l);
    void setLeader(const std::string& l);
    void setParticipants(const std::vector<std::string>& p);
    void setResult(const std::string& r);


    void display(bool compact = false) const;

    // Comparison operators for sorting
    bool operator<(const Event& other) const;
    bool operator>(const Event& other) const;
    bool operator==(const Event& other) const;

    // Helper function for date string
    std::string getDateString() const;
};

#endif // EVENT_H