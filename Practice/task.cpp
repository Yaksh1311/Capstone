#include <iostream>
using namespace std;

class Date{
    int date,month,year;
    public:
    Date(int date,int month,int year){
        this->date=date;
        this->month=month;
        this->year=year;
    }
};

void addtask(string Username){
    string task,description;
    int Importance_Level,Duration_Days,frequency;
    char yn;
    
    cout<<"Enter Task : "<<endl;
    cin>>task;
    cout<<"Add Task Description : "<<endl;
    cin>>description;
    do{
    cout<<"Enter the Importance level(in percentage) : "<<endl;
    cin>>Importance_Level;
    if(Importance_Level<0 || Importance_Level>100){
        cout<<"Error:Importance Level has to be between 0 and 100"<<endl;
    }
    }
    while(Importance_Level<0 || Importance_Level>100);
    
    cout<<"Do you want this task to be repeated?"<<endl<<"Enter 'y' for yes else 'n' for no"<<endl;
    cin>>yn;
    
    if(yn=='y')
        {
            cout<<"After how many days do you want to add the task again? : ";
            cin>>Duration_Days;
            cout<<"How many times do you want the task to be repeated? : ";
            cin>>frequency;
        }
    string status="pending";
}


int main() {
  string s="rishank";
  addtask(s);

    return 0;
}