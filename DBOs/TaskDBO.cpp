#include <bits/stdc++.h>
using namespace std;
#include "DateDBO.hpp"
#include "TaskDBO.hpp"

int tid = 0;

void addTask(string username){
    string task, description, status = "Pending", Deadline;
    int Importance_Level, Duration_Days = 0, frequency = 0;
    char yn;
    tid++;
    cout<<"Enter Task: "<<endl;
    cin>>task;
    cout<<"Add Task Description: "<<endl;
    cin>>description;
    cout << "Enter Deadline in DD/MM/YYYY format: "<<endl;
    cin >> Deadline;
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
    Task t(tid, task, description, Deadline, status, Importance_Level, frequency, Duration_Days);

    fstream fout;
    fout.open("tasks.csv", ios::out | ios::app);
    string entry = username + ',' + to_string(t.taskID) + ',' + task + ',' + description + ',' + Deadline + ',' + to_string(Importance_Level) +
    ',' + to_string(frequency) + ',' + to_string(Duration_Days) + ',' +status + "\n";
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

void editRecord(string username, int id){
    ifstream fin("tasks.csv");
    ofstream tempFile("temp.csv");
    string line;
    string newrec, entry;
    while(getline(fin, line)){
        vector<string> t = split(line, ',');
        if(t[0] == username && t[1] == to_string(id)){
            while(true){
                cout << "Which field do you want to edit?\n";
                cout << "1. Task\n2. Description\n3. Deadline\n4. Importance Level\n5. Day Cycle\n6. Frequency\n";
                int choice;
                cout << "Enter your choice:\n";
                cin >> choice;
                cout << "Enter new value for the field:\n";
                cin >> newrec;
                if(choice == 1){
                    entry = username + ',' + to_string(id) + ',' + newrec + ',' + t[3] + ',' + t[4] + ',' + t[5] + ',' + t[6] + ',' + t[7] + ',' + t[8] + "\n";
                    break;
                }
                else if(choice == 2){
                    entry = username + ',' + to_string(id) + ',' + t[2] + ',' + newrec + ',' + t[4] + ',' + t[5] + ',' + t[6] + ',' + t[7] + ',' + t[8] + "\n";
                    break;
                }
                else if(choice == 3){
                    entry = username + ',' + to_string(id) + ',' + t[2] + ',' + t[3] + ',' + newrec + ',' + t[5] + ',' + t[6] + ',' + t[7] + ',' + t[8] + "\n";
                    break;
                }
                else if(choice == 4){
                    entry = username + ',' + to_string(id) + ',' + t[2] + ',' + t[3] + ',' + t[4] + ',' + newrec + ',' + t[6] + ',' + t[7] + ',' + t[8] + "\n";
                    break;
                }
                else if(choice == 5){
                    entry = username + ',' + to_string(id) + ',' + t[2] + ',' + t[3] + ',' + t[4] + ',' + t[5] + ',' + newrec + ',' + t[7] + ',' + t[8] + "\n";
                    break;
                }
                else if(choice == 6){
                    entry = username + ',' + to_string(id) + ',' + t[2] + ',' + t[3] + ',' + t[4] + ',' + t[5] + ',' + t[6] + ',' + newrec + ',' + t[8] + "\n";
                    break;
                }
            }
            tempFile << entry;
        }
        else{
            tempFile << line << "\n";
        }
    }
    fin.close();
    tempFile.close();
    remove("tasks.csv");
    rename("temp.csv", "tasks.csv");
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
    ifstream fin;
    string fileName = "tasks.csv";
    fin.open(fileName);
    cout << "Username" << setw(20);
    cout << "TaskID" << setw(20);
    cout << "Task" << setw(20);
    cout << "Description" << setw(20);
    cout << "Deadline" << setw(20);
    cout << "ImpLevel" << setw(20);
    cout << "DayCycle" << setw(20);
    cout << "Frequency" << setw(20);
    cout << "Status\n\n";
    vector<string> row;
    while(fin.peek() != EOF){ 
        string rec;
        while(getline(fin, rec)){
            istringstream i(rec);
            string field;
            getline(i, field, ',');
            if(field == username){
                row = split(rec, ',');
                for(auto i : row){
                    cout << i << setw(20);
                }
                cout << "\n";
            }
        }
    }
    cout << "\n";
}
