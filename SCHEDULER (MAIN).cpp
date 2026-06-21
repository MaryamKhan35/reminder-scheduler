#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <string>
#include <limits>
using namespace std;
using namespace chrono;

class Date {
public:
    time_t seconds;
    char dateTxt[30];
    string timeTxt;
    string dayTxt;
    int day;
    string yearTxt;
    int year;
    string monthTxt;
    int month;

    Date() {

        seconds = system_clock::to_time_t(system_clock::now());
        ctime_s(dateTxt, sizeof(dateTxt), &seconds);
        timeTxt = string(dateTxt, 11, 5);
        dayTxt = string(dateTxt, 8, 2);
        day = atoi(dayTxt.c_str());
        yearTxt = string(dateTxt, 20, 4);
        year = atoi(yearTxt.c_str());
        monthTxt = string(dateTxt, 4, 3);

        if (monthTxt == "Jan") month = 1;
        else if (monthTxt == "Feb") month = 2;
        else if (monthTxt == "Mar") month = 3;
        else if (monthTxt == "Apr") month = 4;
        else if (monthTxt == "May") month = 5;
        else if (monthTxt == "Jun") month = 6;
        else if (monthTxt == "Jul") month = 7;
        else if (monthTxt == "Aug") month = 8;
        else if (monthTxt == "Sep") month = 9;
        else if (monthTxt == "Oct") month = 10;
        else if (monthTxt == "Nov") month = 11;
        else month = 12;


        //cout << month << "/" << day << "/" << year << endl;
    }


    int getDate(int fileDay, int fileMonth, int fileYear) {
        day = fileDay;
        month = fileMonth;
        year = fileYear;

        ofstream outFile("ALL_DATES.txt", ios::app);

        if (!outFile.is_open()) {
            cerr << "Error: could not open the file!" << endl;
            cerr << "Enter any key to continue...";
            char tmp;
            cin >> tmp;
            return -1;
        }

        outFile << setw(2) << setfill('0') << fileDay << "/"
            << setw(2) << setfill('0') << fileMonth << "/" << setw(2) << setfill('0')
            << fileYear << endl;
        outFile.close();

        return 0;
    }



};

class Slot {
public:
    int day, month, year;
    int priority;
    string Time;
    string title;
    Slot* next;


    Slot(string s, int Fday, int Fmonth, int Fyear, string Ftime) {

        title = s;
        day = Fday;
        month = Fmonth;
        year = Fyear;
        next = nullptr;
        Time = Ftime;
    }

    Slot(string s, int p, int Fday, int Fmonth, int Fyear) {

        title = s;
        priority = p;
        day = Fday;
        month = Fmonth;
        year = Fyear;
        next = nullptr;
    }

    void storeReminderUser() {
        ofstream outFile("USER_REMINDERS.txt", ios::app);
        if (!outFile.is_open()) {
            cerr << "Error: could not open the file!" << endl;
            cerr << "Enter any key to continue...";
            char tmp;
            cin >> tmp;
        }

        outFile << title << "," << priority << endl;

    }
    void storeReminderTime() {
        ofstream outFile("TIME_REMINDERS.txt", ios::app);
        if (!outFile.is_open()) {
            cerr << "Error: could not open the file!" << endl;
            cerr << "Enter any key to continue...";
            char tmp;
            cin >> tmp;
        }

        outFile << title << "," << Time << endl;

    }
};

struct Time {
    time_t seconds;
    char dateTxt[30];
    string timeTxt;
    string dayTxt;
    int day;
    string yearTxt;
    int year;
    string monthTxt;
    int month;
    Time() {
        seconds = system_clock::to_time_t(system_clock::now());
        ctime_s(dateTxt, sizeof(dateTxt), &seconds);
        timeTxt = string(dateTxt, 11, 5);
        dayTxt = string(dateTxt, 8, 2);
        day = atoi(dayTxt.c_str());
        yearTxt = string(dateTxt, 20, 4);
        year = atoi(yearTxt.c_str());
        monthTxt = string(dateTxt, 4, 3);
    }

};

struct Days {
    time_t seconds;
    char dateTxt[30];
    string dayTxt;
    int day;
    string yearTxt;
    int year;
    string monthTxt;
    int month;

    Days() {
        seconds = system_clock::to_time_t(system_clock::now());
        ctime_s(dateTxt, sizeof(dateTxt), &seconds);
        dayTxt = string(dateTxt, 8, 2);
        day = atoi(dayTxt.c_str());
        yearTxt = string(dateTxt, 20, 4);
        year = atoi(yearTxt.c_str());
        monthTxt = string(dateTxt, 4, 3);
    }
};

class Reminder {
public:
    Date date;
    Slot* head;
    bool option;

    Reminder() {
        head = nullptr;
        option = true;
    }

    void addReminderUser() {
        int fileDay, fileMonth, fileYear;
        int priority;
        string title;

        cout << "Enter the Title of the Reminder: ";
        cin >> title;

        while (true) {
            cout << "Enter the Day to be Stored : ";
            cin >> fileDay;

            if (fileDay <= -1 || fileDay >= 32) {
                cout << "Invalid Day Entered! Enter Again. " << endl;
            }

            else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric value.\n";
            }

            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the Month to be Stored : ";
            cin >> fileMonth;

            if (fileMonth <= -1 || fileMonth >= 13) {
                cout << "Invalid Month Entered! Enter Again. " << endl;
            }

            else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric value.\n";
            }

            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the Year to be Stored : ";
            cin >> fileYear;

            if (fileYear < 23) {
                cout << "Invalid Year Entered! Enter Again. " << endl;
            }

            else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric value.\n";
            }

            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the Priority (Higher Value = Higher Priority) : ";
            cin >> priority;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric value.\n";
            }
            else {
                break;
            }
        }


        Slot* newNode = new Slot(title, priority, fileDay, fileMonth, fileYear);
        newNode->storeReminderUser();

        if (head == nullptr || priority > head->priority) {
            newNode->next = head;
            head = newNode;
            date.getDate(newNode->day, newNode->month, newNode->year);
        }
        else {
            Slot* temp = head;
            while (temp->next != nullptr && priority <= temp->next->priority) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            date.getDate(newNode->day, newNode->month, newNode->year);
        }
    }

    void addReminderTime() {


        int fileDay, fileMonth, fileYear;
        string title, fileTime;

        cout << "Enter the Title of the Reminder: ";
        cin >> title;

        while (true) {
            cout << "Enter the Day to be Stored : ";
            cin >> fileDay;

            if (fileDay <= -1 || fileDay >= 32) {
                cout << "Invalid Day Entered! Enter Again. " << endl;
            }

            else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric value.\n";
            }

            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the Month to be Stored : ";
            cin >> fileMonth;

            if (fileMonth <= -1 || fileMonth >= 13) {
                cout << "Invalid Month Entered! Enter Again. " << endl;
            }

            else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric value.\n";
            }

            else {
                break;
            }
        }

        while (true) {
            cout << "Enter the Year to be Stored : ";
            cin >> fileYear;

            if (fileYear < 23) {
                cout << "Invalid Year Entered! Enter Again. " << endl;
            }

            else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a numeric value.\n";
            }

            else {
                break;
            }
        }

        Time current;
        while (true) {
            cout << "Enter the Time (HH:MM) : ";
            cin >> fileTime;

            if (fileTime < current.timeTxt) {
                cout << "Invalid time Entered! Enter Again. " << endl;
            }
            else {
                break;
            }
        }



        Slot* newNode = new Slot(title, fileDay, fileMonth, fileYear, fileTime);
        newNode->storeReminderTime();

        if (head == nullptr || fileTime > date.timeTxt) {
            newNode->next = head;
            head = newNode;
            date.getDate(newNode->day, newNode->month, newNode->year);
        }
        else {
            Slot* temp = head;
            while (temp->next != nullptr && fileTime <= temp->next->Time) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            date.getDate(newNode->day, newNode->month, newNode->year);

            ofstream outFile("ALL_DATES.txt", ios::app);

            if (!outFile.is_open()) {
                cerr << "Error: could not open the file!" << endl;
                cerr << "Enter any key to continue...";
                char tmp;
                cin >> tmp;
            }

            outFile << setw(2) << setfill('0') << fileMonth << "/"
                << setw(2) << setfill('0') << fileDay << "/" << setw(2) << setfill('0')
                << fileYear << fileTime << endl;
            outFile.close();
        }


    }

    void deleteReminder() {
        if (head != nullptr) {
            Slot* temp = head;
            head = head->next;
            delete temp;
            cout << "Reminder Deleted! " << endl;
        }
        else {
            cout << "PriorityQueue is empty. Cannot pop." << endl;
        }
    }


    bool empty() const {
        return head == nullptr;
    }

    void highPriorFirst() {
        bool swapped;
        Slot* currentNode;
        Slot* lastNode = nullptr;

        do {
            swapped = false;
            currentNode = head;
            while (currentNode != nullptr && currentNode->next != lastNode) {

                if (currentNode->priority < currentNode->next->priority) {
                    swap(currentNode->title, currentNode->next->title);
                    swap(currentNode->day, currentNode->next->day);
                    swap(currentNode->month, currentNode->next->month);
                    swap(currentNode->year, currentNode->next->year);
                    swap(currentNode->priority, currentNode->next->priority);
                    swapped = true;
                }
                currentNode = currentNode->next;
            }
            lastNode = currentNode;

        } while (swapped);
    }
    void lowPriorFirst() {
        bool swapped;
        Slot* currentNode;
        Slot* lastNode = nullptr;

        do {
            swapped = false;
            currentNode = head;
            while (currentNode != nullptr && currentNode->next != lastNode) {

                if (currentNode->priority > currentNode->next->priority) {
                    swap(currentNode->title, currentNode->next->title);
                    swap(currentNode->day, currentNode->next->day);
                    swap(currentNode->month, currentNode->next->month);
                    swap(currentNode->year, currentNode->next->year);
                    swap(currentNode->priority, currentNode->next->priority);
                    swapped = true;
                }
                currentNode = currentNode->next;
            }

            lastNode = currentNode;

        } while (swapped);
    }
    void displayReminderUser() {
        Slot* temp = head;
        if (temp == nullptr) {
            cout << "There are No Reminders! " << endl;
        }
        else {
            char reminderOption;
            cout << "Choose the Following: " << endl;
            cout << "1. High Priority First " << endl;
            cout << "2. Low Priority First " << endl;

            while (true) {
                cin >> reminderOption;

                if (reminderOption <= '0' || reminderOption >= '3') {
                    cout << "Invalid Option Entered! Enter Again. " << endl;
                }

                else if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a numeric value.\n";
                }

                else {
                    break;
                }
            }


            if (reminderOption == '1') {
                highPriorFirst();



            }
            else if (reminderOption == '2') {
                lowPriorFirst();

            }

            Days checkDay;
            if (checkDay.day == temp->day) {
                cout << "The Reminder : ' " << head->title << " ' is due today. " << endl;
            }

            while (temp != nullptr) {
                cout << "Reminder: " << temp->title << endl;
                cout << "The Date is:  " << temp->day << " / " << temp->month << " / " << temp->year << ", Priority: " << temp->priority << endl;
                temp = temp->next;
            }
            cout << "----------------------------" << endl;
        }

    }


    void closeReminderFirst() {
        bool swapped;
        Slot* currentNode;
        Slot* lastNode = nullptr;

        do {
            swapped = false;
            currentNode = head;
            while (currentNode != nullptr && currentNode->next != lastNode) {

                if (currentNode->Time > currentNode->next->Time) {
                    swap(currentNode->title, currentNode->next->title);
                    swap(currentNode->day, currentNode->next->day);
                    swap(currentNode->month, currentNode->next->month);
                    swap(currentNode->year, currentNode->next->year);
                    swap(currentNode->Time, currentNode->next->Time);
                    swapped = true;
                }
                currentNode = currentNode->next;
            }
            lastNode = currentNode;

        } while (swapped);
    }
    void lateReminderFirst() {

        bool swapped;
        Slot* currentNode;
        Slot* lastNode = nullptr;

        do {
            swapped = false;
            currentNode = head;
            while (currentNode != nullptr && currentNode->next != lastNode) {

                if (currentNode->Time < currentNode->next->Time) {
                    swap(currentNode->title, currentNode->next->title);
                    swap(currentNode->day, currentNode->next->day);
                    swap(currentNode->month, currentNode->next->month);
                    swap(currentNode->year, currentNode->next->year);
                    swap(currentNode->Time, currentNode->next->Time);
                    swapped = true;
                }
                currentNode = currentNode->next;
            }
            lastNode = currentNode;

        } while (swapped);
    }
    void displayReminderTime() {
        Slot* temp = head;
        if (temp == nullptr) {
            cout << "There are No Reminders! " << endl;
        }
        else {
            char reminderOption;
            cout << "Choose the Following: " << endl;
            cout << "1. Close Reminder First " << endl;
            cout << "2. Late Reminder First " << endl;
            cin >> reminderOption;

            if (reminderOption == '1') {
                closeReminderFirst();

            }
            else if (reminderOption == '2') {
                lateReminderFirst();
            }

            Time checkTime;
            cout << "- Reminders are Listed: " << endl;
            while (temp != nullptr) {
                if (checkTime.timeTxt == temp->Time || checkTime.day == temp->day) {
                    cout << "The Reminder : ' " << temp->title << " ' is due right now. " << endl;
                }
                else {
                    cout << "Reminder: " << temp->title << endl;
                    cout << "The Date is:  " << temp->day << " / " << temp->month << " / " << temp->year << ", Time: " << temp->Time << endl;
                }

                temp = temp->next;
            }
            cout << "----------------------------" << endl;
        }

    }


};

void selectPriority(Reminder& reminderQueue) {
    char prior;
    cout << "Choose the Following Priority: " << endl;
    cout << "1. User Defined " << endl;
    cout << "2. Time Based " << endl;
    cin >> prior;
    if (prior == '1') {
        reminderQueue.option = true;
    }
    else if (prior == '2') {
        reminderQueue.option = false;
    }
}

void selectOption(Reminder& reminderQueue, char mainOption) {
    if (mainOption == '1') {
        if (reminderQueue.option == true) {
            reminderQueue.addReminderUser();
        }
        else if (reminderQueue.option == false) {
            reminderQueue.addReminderTime();

        }

    }

    else if (mainOption == '2') {
        if (reminderQueue.option == true) {
            reminderQueue.deleteReminder();
        }
        else if (reminderQueue.option == false) {
            reminderQueue.deleteReminder();

        }
    }

    else if (mainOption == '3') {

        if (reminderQueue.option == true) {
            reminderQueue.displayReminderUser();
        }
        else if (reminderQueue.option == false) {
            reminderQueue.displayReminderTime();

        }
    }
}

void userInterface() {
    system("color E4");
}


void SCHEDULER() {
    userInterface();
    Reminder reminderQueue;
    bool mainCheck = true;
    char mainOption;
    bool selectionCheck = true;

    while (mainCheck) {
        cout << " - Scheduler - " << endl;
        cout << "1. Add Reminder " << endl;
        cout << "2. Delete Reminder " << endl;
        cout << "3. View Reminders " << endl;
        cout << "4. Exit " << endl;
        cin >> mainOption;


        if (mainOption >= '1' && mainOption <= '3') {
            if (mainOption == '1') {
                if (selectionCheck == true) {
                    selectPriority(reminderQueue);
                    selectOption(reminderQueue, mainOption);
                    selectionCheck = false;

                }
                else {
                    selectOption(reminderQueue, mainOption);
                }
            }
            else {
                selectOption(reminderQueue, mainOption);
            }

        }
        else if (mainOption == '4') {
            mainCheck = false;
        }
        else {
            system("CLS");
            cout << "Error! Invalid Key Entered. " << endl;

        }
    }

}


int main() {

    SCHEDULER();

}