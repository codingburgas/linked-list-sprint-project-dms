#include "UserInterface.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

UserInterface::UserInterface(Database& database) : db(database) {}

void UserInterface::run() {
    bool running = true;

    // Try to load existing database
    if (!db.loadFromFile()) {
        cout << "Would you like to load sample data? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(choice) == 'y') {
            db.addSampleData();
            cout << "Sample data loaded successfully!" << endl;
        }
    }

    while (running) {
        clearScreen();
        displayMainMenu();

        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            viewAllEvents();
            break;
        case 2:
            searchByName();
            break;
        case 3:
            searchByYear();
            break;
        case 4:
            searchByYearRange();
            break;
        case 5:
            addNewEvent();
            break;
        case 6:
            modifyEvent();
            break;
        case 7:
            deleteEvent();
            break;
        case 8:
            loadDatabase();
            break;
        case 9:
            saveDatabase();
            break;
        case 0:
            if (db.isModified()) {
                cout << "Database has unsaved changes. Save before exiting? (y/n): ";
                char saveChoice;
                cin >> saveChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (tolower(saveChoice) == 'y') {
                    saveDatabase();
                }
            }
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            waitForKey();
            break;
        }
    }

    cout << "Thank you for using the PastPort . Goodbye!" << endl;
}

void UserInterface::displayMainMenu() const {
    cout << "=======================================" << endl;
    cout << "    PastPort " << endl;
    cout << "=======================================" << endl;
    cout << "1. View All Events" << endl;
    cout << "2. Search by Name" << endl;
    cout << "3. Search by Year" << endl;
    cout << "4. Search by Year Range" << endl;
    cout << "5. Add New Event" << endl;
    cout << "6. Modify Event" << endl;
    cout << "7. Delete Event" << endl;
    cout << "8. Load Event from File" << endl;
    cout << "9. Save Event to File" << endl;
    cout << "0. Exit" << endl;
    cout << "=======================================" << endl;
    cout << "Events in database: " << db.getEventCount() << endl;
    cout << "=======================================" << endl;
}

void UserInterface::viewAllEvents() const {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "           ALL EVENTS" << endl;
    cout << "=======================================" << endl;

    const auto& events = db.getAllEvents();
    if (events.empty()) {
        cout << "No events in the database." << endl;
        waitForKey();
        return;
    }

    const int eventsPerPage = 5;
    int currentPage = 0;
    int totalPages = (events.size() + eventsPerPage - 1) / eventsPerPage;
    bool viewing = true;

    while (viewing) {
        clearScreen();
        cout << "=======================================" << endl;
        cout << "           ALL EVENTS" << endl;
        cout << "=======================================" << endl;
        cout << "Page " << (currentPage + 1) << " of " << totalPages << endl;
        cout << "---------------------------------------" << endl;

        int startIdx = currentPage * eventsPerPage;
        int endIdx = min(startIdx + eventsPerPage, static_cast<int>(events.size()));

        for (int i = startIdx; i < endIdx; ++i) {
            displayEvent(events[i], i);
        }

        cout << "---------------------------------------" << endl;
        cout << "Navigation: [P]revious, [N]ext, [B]ack to menu: ";
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (toupper(choice)) {
        case 'P':
            if (currentPage > 0) currentPage--;
            break;
        case 'N':
            if (currentPage < totalPages - 1) currentPage++;
            break;
        case 'B':
            viewing = false;
            break;
        default:
            break;
        }
    }
}

void UserInterface::searchByName() const {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "           SEARCH BY NAME" << endl;
    cout << "=======================================" << endl;

    string query = getStringInput("Enter search term: ");
    auto results = db.searchByName(query);

    clearScreen();
    cout << "=======================================" << endl;
    cout << "           SEARCH RESULTS" << endl;
    cout << "=======================================" << endl;
    cout << "Found " << results.size() << " events matching '" << query << "'" << endl;
    cout << "---------------------------------------" << endl;

    displayEvents(results);
    waitForKey();
}

void UserInterface::searchByYear() const {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "           SEARCH BY YEAR" << endl;
    cout << "=======================================" << endl;

    int year = getIntInput("Enter year to search: ");
    auto results = db.searchByYear(year);

    clearScreen();
    cout << "=======================================" << endl;
    cout << "           SEARCH RESULTS" << endl;
    cout << "=======================================" << endl;
    cout << "Found " << results.size() << " events in year " << year << endl;
    cout << "---------------------------------------" << endl;

    displayEvents(results);
    waitForKey();
}

void UserInterface::searchByYearRange() const {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "        SEARCH BY YEAR RANGE" << endl;
    cout << "=======================================" << endl;

    int startYear = getIntInput("Enter start year: ");
    int endYear = getIntInput("Enter end year: ");

    if (startYear > endYear) {
        swap(startYear, endYear);
    }

    auto results = db.searchByYearRange(startYear, endYear);

    clearScreen();
    cout << "=======================================" << endl;
    cout << "           SEARCH RESULTS" << endl;
    cout << "=======================================" << endl;
    cout << "Found " << results.size() << " events between " << startYear << " and " << endYear << endl;
    cout << "---------------------------------------" << endl;

    displayEvents(results);
    waitForKey();
}

void UserInterface::addNewEvent() {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "           ADD NEW EVENT" << endl;
    cout << "=======================================" << endl;

    int year = getIntInput("Enter year: ");
    string name = getStringInput("Enter event name: ");
    string location = getStringInput("Enter location: ");
    string keyFigures = getStringInput("Enter key figures (separated by commas): ");

    Event newEvent(year, name, location, keyFigures);
    db.addEvent(newEvent);

    cout << "Event added successfully!" << endl;
    waitForKey();
}

void UserInterface::modifyEvent() {
    if (db.getEventCount() == 0) {
        cout << "No events in the database to modify." << endl;
        waitForKey();
        return;
    }

    clearScreen();
    cout << "=======================================" << endl;
    cout << "           MODIFY EVENT" << endl;
    cout << "=======================================" << endl;

    size_t index = getIntInput("Enter event number to modify (1-" + to_string(db.getEventCount()) + "): ") - 1;

    if (index >= db.getEventCount()) {
        cout << "Invalid event number." << endl;
        waitForKey();
        return;
    }

    Event event = db.getEvent(index);

    cout << "Current event details:" << endl;
    displayEvent(event, index);
    cout << "---------------------------------------" << endl;

    cout << "Enter new details (leave blank to keep current value):" << endl;

    string input;

    cout << "Year [" << event.getYear() << "]: ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            event.setYear(stoi(input));
        }
        catch (const exception& e) {
            cout << "Invalid year. Keeping current value." << endl;
        }
    }

    cout << "Name [" << event.getName() << "]: ";
    getline(cin, input);
    if (!input.empty()) {
        event.setName(input);
    }

    cout << "Location [" << event.getLocation() << "]: ";
    getline(cin, input);
    if (!input.empty()) {
        event.setLocation(input);
    }

    cout << "Key Figures [" << event.getKeyFigures() << "]: ";
    getline(cin, input);
    if (!input.empty()) {
        event.setKeyFigures(input);
    }

    if (db.updateEvent(index, event)) {
        cout << "Event updated successfully!" << endl;
    }
    else {
        cout << "Failed to update event." << endl;
    }

    waitForKey();
}

void UserInterface::deleteEvent() {
    if (db.getEventCount() == 0) {
        cout << "No events in the database to delete." << endl;
        waitForKey();
        return;
    }

    clearScreen();
    cout << "=======================================" << endl;
    cout << "           DELETE EVENT" << endl;
    cout << "=======================================" << endl;

    size_t index = getIntInput("Enter event number to delete (1-" + to_string(db.getEventCount()) + "): ") - 1;

    if (index >= db.getEventCount()) {
        cout << "Invalid event number." << endl;
        waitForKey();
        return;
    }

    Event event = db.getEvent(index);

    cout << "Are you sure you want to delete this event?" << endl;
    displayEvent(event, index);
    cout << "Delete? (y/n): ";

    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tolower(choice) == 'y') {
        if (db.deleteEvent(index)) {
            cout << "Event deleted successfully!" << endl;
        }
        else {
            cout << "Failed to delete event." << endl;
        }
    }
    else {
        cout << "Deletion cancelled." << endl;
    }

    waitForKey();
}

void UserInterface::loadDatabase() {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "           LOAD DATABASE" << endl;
    cout << "=======================================" << endl;

    if (db.isModified()) {
        cout << "Current database has unsaved changes." << endl;
        cout << "Loading will discard these changes." << endl;
        cout << "Continue? (y/n): ";

        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(choice) != 'y') {
            cout << "Load operation cancelled." << endl;
            waitForKey();
            return;
        }
    }

    if (db.loadFromFile()) {
        cout << "Database loaded successfully!" << endl;
        cout << "Loaded " << db.getEventCount() << " events." << endl;
    }
    else {
        cout << "Failed to load database or file not found." << endl;
    }

    waitForKey();
}

void UserInterface::saveDatabase() const {
    clearScreen();
    cout << "=======================================" << endl;
    cout << "           SAVE DATABASE" << endl;
    cout << "=======================================" << endl;

    if (db.saveToFile()) {
        cout << "Database saved successfully!" << endl;
        cout << "Saved " << db.getEventCount() << " events." << endl;
    }
    else {
        cout << "Failed to save database." << endl;
    }

    waitForKey();
}

void UserInterface::displayEvent(const Event& event, size_t index) const {
    cout << "Event #" << (index + 1) << ":" << endl;
    cout << "  Year: " << event.getYear() << endl;
    cout << "  Name: " << event.getName() << endl;
    cout << "  Location: " << event.getLocation() << endl;
    cout << "  Key Figures: " << event.getKeyFigures() << endl;
    cout << "---------------------------------------" << endl;
}

void UserInterface::displayEvents(const vector<Event>& events) const {
    if (events.empty()) {
        cout << "No events found." << endl;
        return;
    }

    for (size_t i = 0; i < events.size(); ++i) {
        displayEvent(events[i], i);
    }
}

int UserInterface::getIntInput(const string& prompt) const {
    int value;
    bool validInput = false;

    while (!validInput) {
        cout << prompt;
        string input;
        getline(cin, input);

        try {
            value = stoi(input);
            validInput = true;
        }
        catch (const exception& e) {
            cout << "Invalid input. Please enter a number." << endl;
        }
    }

    return value;
}

string UserInterface::getStringInput(const string& prompt) const {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

void UserInterface::clearScreen() const {
    // This is system-dependent
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UserInterface::waitForKey() const {
    cout << "Press Enter to continue...";
    cin.get();
}