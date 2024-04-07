#include <bits/stdc++.h>
#include "DateDBO.hpp"
#include "TextTable.h"
#include "PriorityQueue.hpp"

using namespace std;


TextTable t('-', '|', '+' );


    
bool PriorityQueue::isEmpty(){
    return frontNode == nullptr;
}

float priorityCalc(int diff, int imp){
    float pr=0.8*diff+0.2*imp;
    return pr;
}

void PriorityQueue::pqEntry(string &username){
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
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        vector<string> dateElements = split(row[4], '/');
        Date d2(stoi(dateElements[0]), stoi(dateElements[1]), stoi(dateElements[2]));
        if(username==row[0] && difference(d1, d2)<=4 && row[8] == "Pending"){
            float priority = priorityCalc(difference(d1,d2), stoi(row[5]));
            enqueue(priority, stoi(row[1]));
        }
    }   
}
void PriorityQueue::enqueue(int p, int tid){
    Node *newNode = new Node(tid);
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

void PriorityQueue::displayQueue(){
    Node* temp = frontNode;
    while(temp != NULL){
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
                t.add(row[1]);
                t.add(row[2]);
                t.add(row[5]);
                t.add(row[4]);
                t.endOfRow();
            }
        }        
    }
}