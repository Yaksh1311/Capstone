#include <bits/stdc++.h>
#include "DBOs/DateDBO.hpp"
#include "DBOs/TaskDBO.hpp"
#include "DBOs/PriorityQueue.hpp"
#include "DBOs/UserlistDBO.hpp"

void sleep(float seconds){
    clock_t startClock = clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    while(clock() < startClock+secondsAhead);
    return;
}

void Center_allign(string& text, int width) {
    int left_padding = (width - text.length()) / 2;
    cout <<setw(left_padding + text.length()) << text << endl;
}

void menu(string Username){
    int choice;
    int x = 1;
    PriorityQueue pq;
    while(true){
        sleep(1.5);
        string text = "Main Menu";
        int console_width = 90; 
        Center_allign(text, console_width);

        cout<<"1. Add Task\n";
        cout<<"2. Delete Task\n";
        cout<<"3. Edit Task\n";
        cout<<"4. Complete Task\n";
        cout<<"5. Display Tasks\n";
        cout<<"6. Change your password.\n";
        cout<<"7. Exit.\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        if(choice == 1){
            addTask(Username);
        }
        else if(choice == 2){
            deleteTask(Username);
        }
        else if(choice == 3){
            int id;
            cout << "Enter Task ID of the task to be edited:\n";
            cin >> id;
            editRecord(Username, id);
        }
        else if(choice == 4){
            completeTask(Username);
        }
        else if(choice == 5){
            displayTask(Username);
        }
        else if(choice == 6){
            change_pass(Username);
        }
        else if(choice == 7){
            cout << "Thank You\n";
            break;
        }
        else{
            cout<<"Enter a valid choice."<<endl;
        }    
   }
}

int main(){
    cout << "Welcome to Task Scheduler and Reminder\n";
    sleep(1.0);
    PriorityQueue pq;
    while(true){
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit.\n";
        int c;
        string username;
        cout << "Enter your choice:\n";
        cin >> c;
        if(c == 1){
            cout << "Enter your username:\n";
            cin >> username;
            signup(username);
            menu(username);
            break;
        }
        else if(c == 2){
            cout << "Enter your username:\n";
            cin >> username;
            login(username);
            pq.pqEntry(username);
            pq.displayQueue(username);
            menu(username);
            break;
        }
        else if(c == 3){
            cout << "Thank You.\n";
            break;
        }
        else{
            cout << "Enter valid choice.";
        }
    }
}