#include <iostream>
#include<mysql>
using namespace std;

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

// ------------------ CONNECT TO DB ------------------
void connectDB() {
    conn = mysql_init(0);
    if (!conn) {
        cout << "? mysql_init failed!\n";
        exit(1);
    }

    conn = mysql_real_connect(conn, "localhost", "root", "yourpassword", "CEMS", 3306, NULL, 0);
    if (conn) {
        cout << "? Connected to MySQL Database!\n";
    } else {
        cout << "? Connection Failed: " << mysql_error(conn) << endl;
        exit(1);
    }
}

// ------------------ STUDENT MENU ------------------
void studentMenu(int user_id) {
    int choice;
    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. View Events\n";
        cout << "2. Register for Event\n";
        cout << "3. Give Feedback\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (mysql_query(conn, "SELECT event_id, title, event_date FROM events;")) {
                cout << "? Query Failed: " << mysql_error(conn) << endl;
                continue;
            }
            res = mysql_store_result(conn);
            cout << "\n--- Available Events ---\n";
            while ((row = mysql_fetch_row(res))) {
                cout << row[0] << ". " << row[1] << " on " << row[2] << endl;
            }
            mysql_free_result(res);
        } else if (choice == 2) {
            int event_id;
            cout << "Enter Event ID to register: ";
            cin >> event_id;
            string query = "INSERT INTO registrations(event_id, student_id, status) VALUES(" 
                           + to_string(event_id) + "," + to_string(user_id) + ",'registered');";
            if (mysql_query(conn, query.c_str())) {
                cout << "? Registration Failed: " << mysql_error(conn) << endl;
            } else {
                cout << "? Registered successfully!\n";
            }
        } else if (choice == 3) {
            int event_id, rating;
            string comment;
            cout << "Enter Event ID to give feedback: ";
            cin >> event_id;
            cout << "Enter Rating (1-5): ";
            cin >> rating;
            cin.ignore();
            cout << "Enter Comment: ";
            getline(cin, comment);

            string query = "INSERT INTO feedback(event_id, student_id, rating, comments) VALUES("
                           + to_string(event_id) + "," + to_string(user_id) + "," + to_string(rating) + ",'" + comment + "');";
            if (mysql_query(conn, query.c_str())) {
                cout << "? Feedback Failed: " << mysql_error(conn) << endl;
            } else {
                cout << "? Feedback submitted!\n";
            }
        } else if (choice == 4) {
            cout << "Logging out...\n";
        } else {
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

// ------------------ TEACHER MENU ------------------
void teacherMenu(int user_id) {
    int choice;
    do {
        cout << "\n--- Teacher Menu ---\n";
        cout << "1. Create Event\n";
        cout << "2. View My Events\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string title, date;
            int capacity;
            cout << "Enter Event Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Event Date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter Capacity: ";
            cin >> capacity;

            string query = "INSERT INTO events(title, description, organizer_id, event_date, capacity) VALUES('"
                           + title + "','NA'," + to_string(user_id) + ",'" + date + "'," + to_string(capacity) + ");";
            if (mysql_query(conn, query.c_str())) {
                cout << "? Event creation failed: " << mysql_error(conn) << endl;
            } else {
                cout << "? Event created!\n";
            }
        } else if (choice == 2) {
            string query = "SELECT event_id, title, event_date FROM events WHERE organizer_id=" + to_string(user_id) + ";";
            if (mysql_query(conn, query.c_str())) {
                cout << "? Query Failed: " << mysql_error(conn) << endl;
                continue;
            }
            res = mysql_store_result(conn);
            cout << "\n--- My Events ---\n";
            while ((row = mysql_fetch_row(res))) {
                cout << row[0] << ". " << row[1] << " on " << row[2] << endl;
            }
            mysql_free_result(res);
        } else if (choice == 3) {
            cout << "Logging out...\n";
        } else {
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

// ------------------ ADMIN MENU ------------------
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. View All Events\n";
        cout << "2. Delete Event\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (mysql_query(conn, "SELECT event_id, title, event_date FROM events;")) {
                cout << "? Query Failed: " << mysql_error(conn) << endl;
                continue;
            }
            res = mysql_store_result(conn);
            cout << "\n--- All Events ---\n";
            while ((row = mysql_fetch_row(res))) {
                cout << row[0] << ". " << row[1] << " on " << row[2] << endl;
            }
            mysql_free_result(res);
        } else if (choice == 2) {
            int event_id;
            cout << "Enter Event ID to delete: ";
            cin >> event_id;
            string query = "DELETE FROM events WHERE event_id=" + to_string(event_id) + ";";
            if (mysql_query(conn, query.c_str())) {
                cout << "? Deletion Failed: " << mysql_error(conn) << endl;
            } else {
                cout << "? Event deleted!\n";
            }
        } else if (choice == 3) {
            cout << "Logging out...\n";
        } else {
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

// ------------------ LOGIN ------------------
void login() {
    string email, password;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;

    string query = "SELECT user_id, name, role FROM users WHERE email='" + email + "' AND password='" + password + "';";

    if (mysql_query(conn, query.c_str())) {
        cout << "? Query Failed: " << mysql_error(conn) << endl;
        return;
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res))) {
        int user_id = stoi(row[0]);
        string name = row[1];
        string role = row[2];

        cout << "\n? Welcome " << name << " (" << role << ")\n";

        if (role == "student") studentMenu(user_id);
        else if (role == "teacher") teacherMenu(user_id);
        else if (role == "admin") adminMenu();
    } else {
        cout << "\n? Invalid login!\n";
    }

    mysql_free_result(res);
}

// ------------------ MAIN ------------------
int main() {
    connectDB();
    login();
    mysql_close(conn);
    return 0;
}
