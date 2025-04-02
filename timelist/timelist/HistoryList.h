#ifndef HISTORYLIST_H
#define HISTORYLIST_H

#include "Event.h"
#include <memory>

class Node {
public:
    Event data;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;

    Node(const Event& e) : data(e), next(nullptr), prev(nullptr) {}
};

class HistoryList {
private:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    int size;

public:
    HistoryList() : head(nullptr), tail(nullptr), size(0) {}

  
    void addFirst(const Event& e);
    void addLast(const Event& e);
    void addInOrder(const Event& e);

 
    bool editEvent(int year, int month, const Event& newEvent);


    std::shared_ptr<Node> searchByDate(int year, int month) const;
    std::vector<std::shared_ptr<Node>> searchByTopic(const std::string& topic) const;

 
    bool deleteEvent(int year, int month);

    void displayAll() const;
    void displayTitles() const;
    void displayByTopic(const std::string& topic) const;
    void displayVictories(const std::string& country) const;

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
};

#endif 
