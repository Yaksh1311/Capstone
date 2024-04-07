#include <bits/stdc++.h>
#include "DateDBO.hpp"
#include "TaskDBO.hpp"
#include "PriorityQueue.hpp"
#include "UserlistDBO.hpp"

using namespace std;

void sleep(float seconds){
    clock_t startClock = clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    while(clock() < startClock+secondsAhead);
    return;
}
void clear(){
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

void Center_allign(string& text, int width) {
    int left_padding = (width - text.length()) / 2;
    cout <<setw(left_padding + text.length()) << text << endl;
}

void menu(string Username){
    clear();
    int choice;
    int x = 1;
    PriorityQueue pq;
    while(x){
        pq.pqEntry(Username);
        pq.displayQueue();
        sleep(1.5);
        string text = "Main Menu";
        int console_width = 90; 
        Center_allign(text, console_width);

        cout<<"1. Add Task"<<endl;
        cout<<"2. Delete Task"<<endl;
        cout<<"3. Edit Task"<<endl;
        cout<<"4. Complete Task"<<endl;
        cout<<"5. Change your password."<<endl;
        cout<<"6. Exit."<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice){
            case 1:
                clear();
                addTask(Username);
                break;

            case 2:
                clear();
                deleteTask(Username);
                break;

            case 3:
                clear();
                edit(Username);
                break;

            case 4:
                clear();
                completeTask(Username);
                break;

            case 5:
                clear();
                change_pass(Username);
                break;
            case 6:
                clear();
                x--;
                break;
            default:
                cout<<"You have entered a wrong choice."<<endl;
                break;
        }
   }    
}

int main(){
    cout << "Welcome to Task Scheduler and Reminder";
    sleep(1.0);
    while(true){
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit.";
        int c;
        cout << "Enter your choice:\n";
        cin >> c;
        if(c == 1){
            string username;
            cout << "Enter your username:\n";
            cin >> username;
            signup(username);
        }
        else if(c == 2){
            string username;
            cout << "Enter your username:\n";
            cin >> username;
            login(username);
        }
        else if(c == 3){
            cout << "Thank You.\n";
            return 0;
        }
    }
}