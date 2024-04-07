#include <bits/stdc++.h>
using namespace std;
#pragma once

vector<string> split(string s, char delim);

bool isLeapYear(int year);

int daysInMonth(int m, int y);

class Date{
    private:
        int day;
        int month;
        int year;
    public:
        Date inputDate();
        bool isValidDate();
        string displayDate();
        Date() : day(1), month(1), year(2024){}
        Date(int d, int m, int y) : day(d), month(m), year(y){}
};