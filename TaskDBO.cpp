#include <bits/stdc++.h>
using namespace std;
#include "DateDBO.hpp"
#include "TaskDBO.hpp"
#include "TextTable.h"

TextTable table('-', '|', '+' );

void addTask(string username){
    string task, description, status;
    int Importance_Level, Duration_Days = 0, frequency = 0;
    Date Deadline;
    char yn;
    cout<<"Enter Task: "<<endl;
    cin>>task;
    cout<<"Add Task Description: "<<endl;
    cin>>description;
    Deadline.inputDate();
    do{
        cout<<"Enter the Importance level(in percentage): "<<endl;
        cin>>Importance_Level;
        if(Importance_Level<0 || Importance_Level>100){
            cout<<"Error:Importance Level has to be between 0 and 100"<<endl;
        }
    }
    while(Importance_Level<0 || Importance_Level>100);

    cout << "Do you want this task to be repeated?\n";
    cout << "Enter 'y' for yes else 'n' for no:\n";
    cin>>yn;
    if(tolower(yn)=='y'){            
        cout<<"After how many days do you want to add the task again?\n";
        cin>>Duration_Days;
        cout<<"How many times do you want the task to be repeated?\n";
        cin>>frequency;
    }
    Task t(task, description, Deadline, status, Importance_Level, frequency, Duration_Days);

    fstream fout;
    fout.open("tasks.csv", ios::out | ios::app);
    string entry = username + ',' + to_string(t.taskID) + ',' + task + ',' + description + ',' + Deadline.displayDate() + ',' + to_string(Importance_Level) +
    ',' + to_string(frequency) + ',' + to_string(Duration_Days) + status;
    fout << entry;
    fout.close();
}

void deleteTask(string username){
    fstream fin, fout;
    fin.open("tasks.csv", ios::in);
    fout.open("tasksnew.csv", ios:: out);
    int id, count = 0;
    cout << "Enter the Task ID of the task to be deleted:\n";
    cin >> id;
    vector<string> row;
    string line, word;
    while(!fin.eof()){
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        int row_size = row.size();
        if(id != stoi(row[1])){
            if(!fin.eof()){
                for(int i = 0; i < row_size-1; i++){
                    fout << row[i] << ",";
                }
                fout << row[row_size-1] << "\n";
            }
        }
        else{
            count = 1;
        }
        if(fin.eof()){
            break;
        }
    }
    if(count == 1){
        cout << "Task deleted successfully.\n";
    }
    else{
        cout << "Task not found.\n";
        deleteTask(username);
    }
    fin.close();
    fout.close();
    remove("tasks.csv");
    rename("tasksnew.csv", "tasks.csv");
}

void editTask(int x,string username){
    int count = 0, id;
    cout << "Enter Task ID of the task to be edited:\n";
    cin >> id;
    fstream fin,fout;
    fin.open("tasks.csv", ios::in);
    fout.open("tasksnew.csv", ios::out);
    vector<string> r;
    string newdetail,line,word;
    cout<<"Enter new detail: "<<endl;
    cin >> newdetail;

    while(!fin.eof()){ 
        r.clear();
        getline(fin, line);
        stringstream s(line);

        while( getline(s, word, ',')){
            r.push_back(word);
        }

        if(r[0] == username && r[1] == to_string(id)){
            count = 1;
            stringstream change;
            change << newdetail;
            r[x] = change.str();
            if(!fin.eof()){
                for(int i=0; i<r.size() - 1; i++){
                    fout << r[x] << ",";
                }
                fout << r[r.size() - 1] << endl;
            }
        }
        else{
            if(!fin.eof()){
                for(int i=0; i<r.size() - 1; i++){
                    fout << r[x] << ",";
                }
                fout << r[r.size() - 1] << endl;
            }
        }
        if(fin.eof())
            break;
    }
    if(count == 0){
        cout << "Record Not Found." << endl; 
    }
    fin.close();
    fout.close();

    remove("tasks.csv");
    rename("tasksnew.csv" , "tasks.csv");
}

void edit(string &username){
    int index;
    cout<<"1. Task"<<endl;
    cout<<"2. Description"<<endl;
    cout<<"3. Deadline"<<endl;
    cout<<"4. Importance Level"<<endl;
    cout<<"5. Day Cycle Frequency"<<endl;
    cout<<"6. Frequency of Repeatation"<<endl;
    cin>>index;
    switch(index+1){
        case 2:
            editTask(2,username);
            break;
        case 3:
            editTask(3,username);
            break;
        case 4:
            editTask(4,username);
            break;
        case 5:
            editTask(5,username);
            break;
        case 6:
            editTask(6,username);
            break;
        case 7:
            editTask(7,username);
        default:
            cout<<"Wrong choice. Please enter again"<<endl;
            edit(username); 
            break;
    }
}

void completeTask(string username){
    int id;
    cout << "Enter the Task ID of the task which is completed:\n";
    cin >> id;
    fstream fin,fout;
    fin.open("tasks.csv", ios::in);
    fout.open("tasksnew.csv", ios::out);
    vector<string> r;
    string line,word;
    while(!fin.eof()){ 
        r.clear();
        getline(fin, line);
        stringstream s(line);
        while( getline(s, word, ',')){
            r.push_back(word);
        }
        if(r[0] == username && r[1] == to_string(id)){
            stringstream update;
            update << "Completed";
            r[8] = update.str();
            if(stoi(r[7]) != 0){
                int rep = stoi(r[7])-1;
                stringstream c;
                c << rep;
                r[7] = c.str();
                vector<string> date = split(r[4], ',');
                int day = stoi(date[0]);
                int month = stoi(date[1]);
                int year = stoi(date[2]);
                Date d(day, month, year);
                int n = stoi(r[7]);
                d.dateAdd(n);
            }
            if(!fin.eof()){
                for(int i = 0; i < 8; i++){
                    fout << r[i] << ",";
                }
                fout << r[8] << "\n";
            }
        }
        else{
            if(!fin.eof()){
                for(int i = 0; i < 8; i++){
                    fout << r[i] << ",";
                }
                fout << r[8] << "\n";
            }
        }
        if(fin.eof()){
            break;
        }
    }
    fin.close();
    fout.close();

    remove("tasks.csv");
    rename("tasksnew.csv", "tasks.csv");
}

void displayTask(string username){
    fstream fin;
    fin.open("tasks.csv", ios::in);
    vector<string> r;
    string line,word;
    table.add("TaskID");
    table.add("Task");
    table.add("Description");
    table.add("Deadline");
    table.add("ImpLevel");
    table.add("Day Cycle Frequency");
    table.add("Frequency of Repeatation");
    table.add("Status");
    table.endOfRow();
    while(!fin.eof()){ 
        r.clear();
        getline(fin, line);
        stringstream s(line);
        while( getline(s, word, ',')){
            r.push_back(word);
        }
        if(r[0] == username){
            table.add(r[1]);
            table.add(r[2]);
            table.add(r[3]);
            table.add(r[4]);
            table.add(r[5]);
            table.add(r[6]);
            table.add(r[7]);
            table.add(r[8]);
            table.endOfRow();
        }
    }
}

void missingTask(string username){
    fstream fin,fout;
    fin.open("tasks.csv", ios::in);
    fout.open("tasksnew.csv", ios::out);
    vector<string> r;
    string line,word;
    while(!fin.eof()){ 
        r.clear();
        getline(fin, line);
        stringstream s(line);
        while( getline(s, word, ',')){
            r.push_back(word);
        }
        if(r[0] == username){
            stringstream update;
            update << "Missed";
            r[8] = update.str();
            if(!fin.eof()){
                for(int i = 0; i < 8; i++){
                    fout << r[i] << ",";
                }
                fout << r[8] << "\n";
            }
        }
        else{
            if(!fin.eof()){
                for(int i = 0; i < 8; i++){
                    fout << r[i] << ",";
                }
                fout << r[8] << "\n";
            }
        }
        if(fin.eof()){
            break;
        }
    }
    fin.close();
    fout.close();

    remove("tasks.csv");
    rename("tasksnew.csv", "tasks.csv");
}