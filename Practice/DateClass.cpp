#include <bits/stdc++.h>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(1), month(1), year(2000) {}

    void inputDate() {
        
        cin>>day;
        cin>>month;
        cin>>year;

        if (!isValidDate()) {
            cout << "Invalid date entered. Setting date to default (01/01/2000)." << endl;
            day = 1;
            month = 1;
            year = 2000;
            inputDate();
        }
        
    }

    bool isValidDate() const {
        if (year < 0 || month < 1 || month > 12 || day < 1 || day > daysInMonth()) {
            return false;
        }
        return true;
    }

    int daysInMonth() const {
        const int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int days = daysInMonths[month - 1];
        if (month == 2 && isLeapYear()) {
            days = 29;
        }
        return days;
    }

    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

};