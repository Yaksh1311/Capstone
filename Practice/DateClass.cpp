#include <bits/stdc++.h>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() : day(1), month(1), year(2000) {}
    Date(int dd,int mm,int yyyy) : day(dd), month(mm), year(yyyy){}

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
    
    int daysSinceYearZero() const{
        int days = 0;

        for (int y = 2024; y < year; ++y) {
            bool isLeapYear = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
            if(isLeapYear){
                days+=366;
            }
            else days+=365;
        }

        for (int m = 1; m < month; ++m) {
            static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            days += daysInMonth[m - 1];
            if (m == 2 && (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                days += 1;
            }
        }  

        days += day - 1;

        return days;
    }
};

int difference(const Date& date1, const Date& date2){
    int day1 = date1.daysSinceYearZero();
    int day2 = date2.daysSinceYearZero();
    return day2-day1;
}

int main(){
    Date date1(11,12,2024);
    Date date2(11,1,2025);

    int diff=difference(date1,date2);
    cout<<diff;
}