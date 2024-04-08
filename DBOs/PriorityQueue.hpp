#include <bits/stdc++.h>
#include "DateDBO.hpp"

using namespace std;

float priorityCalc(int diff, int imp);

class Node
{
public:
    float priority;
    int taskid;

    Node *nextNode;
    Node(float p, int id)
    {
        priority = p;
        taskid=id;
        nextNode = NULL;
    }
};

class PriorityQueue{
    public:
        Node *frontNode;
        PriorityQueue(){
            frontNode = nullptr;
        }
        bool isEmpty();
        void enqueue(float p, int tid);
        void pqEntry(string username);
        void displayQueue(string username);
};