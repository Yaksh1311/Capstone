#include <bits/stdc++.h>
#include "DateDBO.hpp"
#include "PriorityQueue.hpp"

using namespace std;

bool PriorityQueue::isEmpty(){
    return frontNode == nullptr;
}

float priorityCalc(int diff, int imp){
    float pr=0.8*diff+0.2*imp;
    return pr;
}

void PriorityQueue::enqueue(float p, int tid){
    Node *newNode = new Node(p, tid);
    if (!frontNode || p > frontNode->priority){
        newNode->nextNode = frontNode;            
        frontNode = newNode;
    }
    else{
        Node *current = frontNode;
        while (current->nextNode && p <=current->priority){
            current = current->nextNode;
        }
        newNode->nextNode = current->nextNode;
        current->nextNode = newNode;
    }
}

void PriorityQueue::pqEntry(string username){
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    auto year = localTime->tm_year + 1900;
    auto month = localTime->tm_mon + 1;     
    auto day = localTime->tm_mday;
    Date d1(day, month, year);
    ifstream fin("tasks.csv");
    vector<string> row;
    string line, word, pass;
    int count = 0;
    while(getline(fin, line)){
        row = split(line, ',');
        vector<string> dateElements = split(row[4], '/');
        Date d2(stoi(dateElements[0]), stoi(dateElements[1]), stoi(dateElements[2]));
        if(username==row[0] && difference(d1, d2)<=4 && row[8] == "Pending"){
            float priority = priorityCalc(difference(d1,d2), stoi(row[5]));
            PriorityQueue::enqueue(priority, stoi(row[1]));
        }
    }   
}

void PriorityQueue::displayQueue(string username){
    Node* temp = frontNode;
    cout << "TaskID" << setw(20);
    cout << "Task" << setw(20);
    cout << "Deadline" << setw(20);
    cout << "Importance Level" << setw(20);
    cout << "Status\n";
    while(temp->nextNode != NULL){
        ifstream fin("tasks.csv");
        vector<string> row;
        string line, word, pass;
        int count = 0;
        while(getline(fin, line)){
            row.clear();
            stringstream s(line);
            while(getline(s, word, ',')){
                row.push_back(word);                
            }
            if(temp->taskid == stoi(row[1])){
                cout << row[1] << setw(20);
                cout << row[2] << setw(20);
                cout << row[4] << setw(20);
                cout << row[5] << setw(20);
                cout << row[8] << "\n";
            }
        }
        frontNode = frontNode->nextNode;      
    }
}
