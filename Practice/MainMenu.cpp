#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void Center_allign(string& text, int width) {
    int left_padding = (width - text.length()) / 2;
    cout <<setw(left_padding + text.length()) << text << endl;
}

void Add_Task(string Username){
    cout<<"Task added successfully."<<endl;
}
void Delete_Task(string Username){
    cout<<"Task Deleted."<<endl;
}
void Edit_Task(string Username){
    cout<<"Task Edited."<<endl;
}
void Complete_Task(string Username){
    cout<<"Task completed"<<endl;
}

void clear(){
    system("cls");
}



void menu(string Username){
    clear();
    int choice;
    int x = 1;
   while(x){
    string text = "Main Menu";
    int console_width = 90; 
    Center_allign(text, console_width);
    
    cout<<"1. Add Task"<<endl;
    cout<<"2. Delete Task"<<endl;
    cout<<"3. Edit Task"<<endl;
    cout<<"4. Complete Task"<<endl;
    cout<<"5. Exit"<<endl;
    cout<<"Enter your choice : ";
    cin>>choice;
    
   
    switch (choice){
        case 1:
        clear();
        Add_Task(Username);
        break;
        
        case 2:
        clear();
        Delete_Task(Username);
        break;
        
        case 3:
        clear();
        Edit_Task(Username);
        break;
        
        case 4:
        clear();
        Complete_Task(Username);
        break;
        
        case 5:
        clear();
        x--;
        break;
        
        default:
        cout<<"You have entered a wrong choice."<<endl;
       break;
    }
   }
    
    
    
}

int main() {
    string s="R";
    menu(s);
    return 0;
}