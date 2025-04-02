#include "HistoryList.h"
#include <iostream>

void HistoryList::addFirst(const Event& e) {
    auto newNode = std::make_shared<Node>(e);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

void HistoryList::addLast(const Event& e) {
    auto newNode = std::make_shared<Node>(e);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void HistoryList::addInOrder(const Event& e) {
    if (isEmpty() || e < head->data) {
        addFirst(e);
    }
    else if (e > tail->data) {
        addLast(e);
    }
    else {
        auto newNode = std::make_shared<Node>(e);
        auto current = head;

        while (current != nullptr && current->data < e) {
            current = current->next;
        }

        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        size++;
    }
}

bool HistoryList::editEvent(int year, int month, const Event& newEvent) {
    auto node = searchByDate(year, month);
    if (node != nullptr) {
        node->data = newEvent;
        return true;
    }
    return false;
}

std::shared_ptr<Node> HistoryList::searchByDate(int year, int month) const {
    Event temp(year, month, "", "", "", "", {}, "");
    auto current = head;

    while (current != nullptr) {
        if (current->data == temp) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Node>> HistoryList::searchByTopic(const std::string& topic) const {
    std::vector<std::shared_ptr<Node>> result;
    auto current = head;

    while (current != nullptr) {
        if (current->data.getTopic() == topic) {
            result.push_back(current);
        }
        current = current->next;
    }
    return result;
}

bool HistoryList::deleteEvent(int year, int month) {
    auto node = searchByDate(year, month);
    if (node == nullptr) return false;

    if (node == head && node == tail) {
        head = tail = nullptr;
    }
    else if (node == head) {
        head = head->next;
        head->prev = nullptr;
    }
    else if (node == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    size--;
    return true;
}

void HistoryList::displayAll() const {
    auto current = head;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

void HistoryList::displayTitles() const {
    auto current = head;
    int count = 1;
    while (current != nullptr) {
        std::cout << count++ << ". " << current->data.getTitle() << " ("
            << current->data.getYear() << ")\n";
        current = current->next;
    }
}

void HistoryList::displayByTopic(const std::string& topic) const {
    auto events = searchByTopic(topic);
    for (const auto& event : events) {
        event->data.display();
    }
}

void HistoryList::displayVictories(const std::string& country) const {
    auto current = head;
    while (current != nullptr) {
        const std::string& result = current->data.getResult();
        if (result.find("victory for " + country) != std::string::npos ||
            result.find(country + " victory") != std::string::npos) {
            current->data.display();
        }
        current = current->next;
    }
}s