#include <bits/stdc++.h>
#include "DateDBO.hpp"

using namespace std;
#pragma once

void addTask(string username);

void deleteTask(string username);

void editRecord(string username, int x);

void completeTask(string username);

void displayTask(string username);

class Task{
    public:
        int taskID, imp_level, frequency, repeat;
        string task, description, status;
        string deadLine;
        Task(){
            status = "Pending";
            repeat = 0;
            frequency = 0;
        }
        Task(int id, string name, string desc, string deadline, string stat, int implevel, int freq, int rep){
            taskID = id;
            task = name;
            description = desc;
            imp_level = implevel;
            deadLine = deadline;
            frequency = freq;
            repeat = rep;
            status = stat;
        }
};
