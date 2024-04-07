#include <bits/stdc++.h>
#include "DateDBO.hpp"
using namespace std;

class Node
{
public:
    int priority;
    int taskid;

    Node *nextNode;
    Node(int id)
    {
        taskid=id;
        nextNode = nullptr;
    }
};

class PriorityQueue
{
    Node *frontNode;

public:
    PriorityQueue()
    {
        frontNode = nullptr;
    }
    bool isEmpty()
    {
        return frontNode == nullptr;
    }

    float priorityCalc(int diff, int imp){
        float pr=0.8*diff+0.2*imp;
        return pr;
    }

    void pqEntry(string &username){
        time_t currentTime = time(nullptr);
        tm* localTime = localtime(&currentTime);
        int year = localTime->tm_year + 1900;
        int month = localTime->tm_mon + 1;     
        int day = localTime->tm_mday;
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
                int priority = priorityCalc(difference(d1,d2), stoi(row[5]));
                enqueue(priority, stoi(row[1]));
            }
        }   
    }

    void enqueue(int p, int tid){
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
};
