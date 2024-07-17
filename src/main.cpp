#include <iostream>
#include <sqlite3.h>
#include <thread>
#include <chrono>

using namespace std;

const char* db = "D:/Shreyash/Placement/Projects/crudapp.db";
bool headerPrinted = false;

void printSeparator(int numColumns) {
    for (int i = 0; i < numColumns; ++i) {
        cout << "-----------------";
    }
    cout << endl;
}

// Callback function to print results in table format
int callback(void* NotUsed, int numColumns, char** columnValues, char** columnNames) {
    if (!headerPrinted) {
        // Print column headers
        for (int i = 0; i < numColumns; ++i) {
            cout << left << setw(30) << columnNames[i];
        }
        cout << endl;

        // Print separator line
        printSeparator(numColumns);

        // Set headerPrinted flag to true
        headerPrinted = true;
    }

    // Print each row
    for (int i = 0; i < numColumns; ++i) {
        cout << left << setw(30) << (columnValues[i] ? columnValues[i] : "NULL");
    }
    cout << endl;

    return 0;
}

int main() {
    
    sqlite3* conn;

    int rc = sqlite3_open(db, &conn);

    if(rc) {
        cout << endl << endl;
        cout << "\t\t ERROR : " << sqlite3_errmsg(conn) << endl;
        return 1;
    } else {
        cout << endl << endl;
        cout << "LOGGED IN !" << endl;
    }

    // Create the employee table if it doesn't exist
    const char* createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS employee (
            ID INTEGER PRIMARY KEY,
            Name TEXT,
            Salary REAL,
            Age INTEGER
        );
    )";
    char* errmsg = nullptr;
    rc = sqlite3_exec(conn, createTableQuery, nullptr, nullptr, &errmsg);
    if(rc != SQLITE_OK) {
        cout << endl << endl;
        cout << "\t\t ERROR : " << errmsg << endl;
        sqlite3_free(errmsg);
        sqlite3_close(conn);
        return 1;
    }

    this_thread::sleep_for(chrono::seconds(3));

    bool exit = false;
    while(!exit) {
        system("cls");
        int val;
        cout << "\t\t Welcome To MySQL Database" << endl;
        cout << "\t\t****************************" << endl;
        cout << "\t\t 1. Insert Data" << endl;
        cout << "\t\t 2. Delete Data" << endl;
        cout << "\t\t 3. Update Data" << endl;
        cout << "\t\t 4. Get / Read data" << endl;
        cout << "\t\t 0. Exit" << endl;
        cout << "\t\t Enter your choice : ";
        cin >> val;
        cin.ignore();

        if(val == 1) {
            system("cls");
            string id, name, salary, age;
            cout << endl << endl;
            cout << "\t\t Enter ID : ";
            getline(cin, id);
            cout << "\t\t Enter Name : ";
            getline(cin, name);
            cout << "\t\t Enter Salary : ";
            getline(cin, salary);
            cout << "\t\t Enter Age : ";
            getline(cin, age);

            string ins = "INSERT INTO EMPLOYEE(ID, Name, Salary, Age) VALUES('"+id+"', '"+name+"', '"+salary+"', '"+age+"')";
            char* errmsg = nullptr;
            rc = sqlite3_exec(conn, ins.c_str(), nullptr, nullptr, &errmsg);
            if(rc != SQLITE_OK){
                cout << endl << endl;
                cout << "\t\t ERROR : " << errmsg << endl;
                sqlite3_free(errmsg);
            }
            else{
                cout << endl << endl;
                cout << "\t\t Data Inserted Successfully" << endl; 
            }
            this_thread::sleep_for(chrono::seconds(5));
        }

        else if(val == 2) {
            system("cls");
            string id;
            cout << "\t\t Enter ID: ";
            cin >> id;
            cin.ignore();

            string del = "DELETE FROM EMPLOYEE WHERE ID = '"+id+"' ";
            char* errmsg = nullptr;
            rc = sqlite3_exec(conn, del.c_str(), nullptr, nullptr, &errmsg);
            if(rc != SQLITE_OK) {
                cout << endl << endl;
                cout << "\t\t Error : " << errmsg << endl;
                sqlite3_free(errmsg);
            }
            else {
                int changes = sqlite3_changes(conn);
                if(changes > 0) {
                    cout << endl << endl;
                    cout << "\t\t Data Deleted Successfully" << endl;
                } 
                else {
                    cout << endl << endl;
                    cout << "\t\t No data found with ID : "  << id << endl;
                }
            }
            this_thread::sleep_for(chrono::seconds(5));
        }

        else if(val == 3) {
            system("cls");
            string id, age, salary;
            cout << "\t\t Enter ID: ";
            cin >> id;
            cout << "\t\t Age: ";
            cin >> age;
            cout << "\t\t Salary: ";
            cin >> salary;
            cin.ignore();

            string upd = "UPDATE EMPLOYEE SET Salary = '"+salary+"', Age = '"+age+"' WHERE ID = '"+id+"' ";
            char* errmsg = nullptr;
            rc = sqlite3_exec(conn, upd.c_str(), nullptr, nullptr, &errmsg);
            if(rc != SQLITE_OK) {
                cout << endl << endl;
                cout << "\t\t Error : " << errmsg << endl;
                sqlite3_free(errmsg);
            }
            else {
                cout << endl << endl;
                cout << "\t\t Data Updated Successfully" << endl;
            }
            this_thread::sleep_for(chrono::seconds(5));
        }

        else if (val == 4) {
            system("cls");
            const char* slct = "SELECT * FROM employee";
            char* errmsg = nullptr;
            rc = sqlite3_exec(conn, slct, callback, nullptr, &errmsg);
            if(rc != SQLITE_OK) {
                cout << endl << endl;
                cout << "\t\t ERROR : " << errmsg << endl;
                sqlite3_free(errmsg);
            }
            this_thread::sleep_for(chrono::seconds(20));
        }

        else if(val == 0) {
            exit = true;
        }

        else{
            cout << endl << endl;
            cout << "\t\t Invalid Input" << endl;
            this_thread::sleep_for(chrono::seconds(3));
        }
    }

    sqlite3_close(conn);
    return 0;
}
