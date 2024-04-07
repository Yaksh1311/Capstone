#include <bits/stdc++.h>
#include "DateDBO.hpp"

using namespace std;
#pragma once

void addTask(string username);

void deleteTask(string username);

void editTask(int x,string username);

void edit(string &username);

void completeTask(string username);

class Task{
    public:
        int taskID = 1, imp_level, frequency, repeat;
        string task, description, status;
        Date deadLine;
        Task(){
            taskID++;
            status = "Pending";
            repeat = 0;
            frequency = 0;
        }
        Task(string name, string desc, Date deadline, string stat, int implevel, int freq, int rep){
            task = name;
            description = desc;
            imp_level = implevel;
            deadLine = deadline;
            frequency = freq;
            repeat = rep;
            status = stat;
        }
};
