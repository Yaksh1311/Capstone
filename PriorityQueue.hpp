#include <bits/stdc++.h>
#include "DateDBO.hpp"
#include "TextTable.h"

using namespace std;

float priorityCalc(int diff, int imp);

class Node
{
public:
    float priority;
    int taskid;

    Node *nextNode;
    Node(int id)
    {
        taskid=id;
        nextNode = nullptr;
    }
};

class PriorityQueue{
    public:
        Node *frontNode;
        PriorityQueue(){
            frontNode = nullptr;
        }
        bool isEmpty();
        void enqueue(int p, int tid);
        void pqEntry(string &username);
        void displayQueue();
};