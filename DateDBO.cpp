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
    cout << "Enter Date in DD/MM/YYYY format:\n";
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