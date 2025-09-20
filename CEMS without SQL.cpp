#include <iostream>
#include <vector>
using namespace std;

// ---------------- Event Struct ----------------
struct Event 
{
    int event_id;
    string title;
    string date;
    string created_by;
};

// Global vector to simulate DB
vector<Event> events;

// ---------------- Base Class ----------------
class User 
{
protected:
    int user_id;
    string name, email, password, role;
public:
    User() {}
    User(int id, string n, string e, string p, string r) 
	{
        user_id = id;
        name = n;
        email = e;
        password = p;
        role = r;
    }
    virtual void displayMenu() = 0; // Pure virtual function
};

// ---------------- Student Class ----------------
class Student : public User 
{
public:
    void displayMenu() override 
	{
        int choice;
        do {
            cout << "\n--- Student Menu ---\n";
            cout << "1. View Events\n";
            cout << "2. Register for Event (dummy)\n";
            cout << "3. Give Feedback (dummy)\n";
            cout << "4. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "\n--- Available Events ---\n";
                    if (events.empty()) {
                        cout << "No events available.\n";
                    } else {
                        for (auto &ev : events) {
                            cout << ev.event_id << ". " << ev.title
                                 << " on " << ev.date
                                 << " (by " << ev.created_by << ")\n";
                        }
                    }
                    break;
                }
                case 2: cout << "Registering for event (dummy)\n"; break;
                case 3: cout << "Giving feedback (dummy)\n"; break;
                case 4: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 4);
    }
};

// ---------------- Teacher Class ----------------
class Teacher : public User 
{
public:
    void displayMenu() override 
	{
        int choice;
        do {
            cout << "\n--- Teacher Menu ---\n";
            cout << "1. Create Event\n";
            cout << "2. View My Events\n";
            cout << "3. Mark Attendance (dummy)\n";
            cout << "4. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    Event ev;
                    ev.event_id = events.size() + 1;
                    cout << "Enter event title: ";
                    cin >> ev.title;
                    cout << "Enter event date: ";
                    cin >> ev.date;
                    ev.created_by = "Teacher"; // later can be dynamic
                    events.push_back(ev);
                    cout << "✅ Event created!\n";
                    break;
                }
                case 2: {
                    cout << "\n--- My Events ---\n";
                    for (auto &ev : events) {
                        if (ev.created_by == "Teacher") {
                            cout << ev.event_id << ". " << ev.title
                                 << " on " << ev.date << "\n";
                        }
                    }
                    break;
                }
                case 3: cout << "Marking attendance (dummy)\n"; break;
                case 4: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 4);
    }
};

// ---------------- Admin Class ----------------
class Admin : public User {
public:
    void displayMenu() override 
	{
        int choice;
        do {
            cout << "\n--- Admin Menu ---\n";
            cout << "1. View All Events\n";
            cout << "2. Delete Event\n";
            cout << "3. Block User (dummy)\n";
            cout << "4. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) 
			{
                case 1: 
				{
                    cout << "\n--- All Events ---\n";
                    if (events.empty()) 
					{
                        cout << "No events available.\n";
                    } else 
					{
                        for (auto &ev : events) 
						{
                            cout << ev.event_id << ". " << ev.title
                                 << " on " << ev.date
                                 << " (by " << ev.created_by << ")\n";
                        }
                    }
                    break;
                }
                case 2: 
				{
                    int id;
                    cout << "Enter event ID to delete: ";
                    cin >> id;
                    bool found = false;
                    for (auto it = events.begin(); it != events.end(); ++it) 
					{
                        if (it->event_id == id) 
						{
                            events.erase(it);
                            cout << "✅ Event deleted!\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) cout << "❌ Event not found!\n";
                    break;
                }
                case 3: cout << "Blocking user (dummy)\n"; break;
                case 4: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 4);
    }
};

// ---------------- Main Program ----------------
int main() {
    int choice;
    User* user = nullptr;

    do {
        cout << "\n=== Campus Event Management System ===\n";
        cout << "1. Login as Student\n";
        cout << "2. Login as Teacher\n";
        cout << "3. Login as Admin\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1: 
                user = new Student();
                user->displayMenu();
                delete user;
                break;
            case 2: 
                user = new Teacher();
                user->displayMenu();
                delete user;
                break;
            case 3: 
                user = new Admin();
                user->displayMenu();
                delete user;
                break;
            case 4: 
                cout << "Exiting program...\n"; break;
            default: 
                cout << "Invalid choice!\n"; break;
        }
    } while (choice != 4);

    return 0;
}
