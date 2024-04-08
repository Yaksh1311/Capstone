#include <bits/stdc++.h>
using namespace std;
#include "DateDBO.hpp"


vector<string> split(string s, char delim){
    vector<string> elements;
    string element;
    istringstream stream(s);
    while(getline(stream, element, delim)){
        elements.push_back(element);
    }
    return elements;
}

bool isLeapYear(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int m, int y){
    const int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = daysInMonths[m - 1];
    if (m == 2 && isLeapYear(y)){
        days = 29;
    }
    return days;
}


Date Date::inputDate(){        
    cout << "Enter Deadline in DD/MM/YYYY format:\n";
    string date;
    cin >> date;
    vector<string> dateElements = split(date, '/');
    int day = stoi(dateElements[0]);
    int month = stoi(dateElements[1]);
    int year = stoi(dateElements[2]);
    if (!isValidDate()){
        cout << "Invalid date entered. Please enter a valid date:\n";
        inputDate();
    }
    return Date(day, month, year);
}

bool Date::isValidDate(){
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > daysInMonth(month, year)){
        return false;
    }
    return true;
}

string Date::displayDate(){
    string date;
    date = to_string(day) + '/' + to_string(month) + '/' + to_string(year);
    return date;
}

int Date::daysSinceYearZero() {
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

int difference(Date date1, Date date2){
    int day1 = date1.daysSinceYearZero();
    int day2 = date2.daysSinceYearZero();
    return day2-day1;
}

string Date::dateAdd(int n){
    Date result = Date(day, month, year); 

    int totalDays = day + n;

    while (true) {
        static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (result.month == 2 && (isLeapYear(year))) {
            if (totalDays > 29) {
                totalDays -= 29;
                result.month++;
            } 
            else {
                result.day = totalDays;
                break;
            }
        } 
        else {
            if (totalDays > daysInMonth[result.month - 1]) {
                totalDays -= daysInMonth[result.month - 1];
                result.month++;
            } 
            else {
                result.day = totalDays;
                break;
            }
        }

        if (result.month > 12) {
            result.month = 1;
            result.year++;
        }
    }

    result.year += (totalDays / 365);
    string res= to_string(result.day)+"/"+to_string(result.month)+"/"+to_string(result.year);
    return res;
}