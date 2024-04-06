#include <bits/stdc++.h>

using namespace std;
void EditFile(int x,string username){
    int count = 0;
    fstream fin,fout;
    fin.open("task.csv", ios::in);
    fout.open("tasknew.csv", ios::out);
    vector<string> r;
    string newdetail,line,word;
    cout<<"Enter new detail: "<<endl;
    cin >> newdetail;

    while(!fin.eof()){ 
        r.clear();
        getline(fin, line);
        stringstream s(line);

        while( getline(s, word, ',')){
            r.push_back(word);
        }

        if(r[0] == username){
            count = 1;
            stringstream change;

            change << newdetail;
            if(!fin.eof()){
                for(int i=0; i<r.size() - 1; i++){
                    fout << r[x] << ",";
                }
                fout << r[r.size() - 1] << endl;
            }
        }
        else{
            if(!fin.eof()){
                for(int i=0; i<r.size() - 1; i++){
                    fout << r[x] << ",";
                }
                fout << r[r.size() - 1] << endl;
            }
        }
        if(fin.eof())
            break;
    }
    if(count == 0){
        cout << "Record Not Found." << endl; 
    }
    fin.close();
    fout.close();

    remove("task.csv");

    rename("tasknew.csv" , "task.csv");
}

void edit(string &username){
    int index;
    cout<<"1. Task"<<endl;
    cout<<"2. Description"<<endl;
    cout<<"3. Deadline"<<endl;
    cout<<"4. Importance Level"<<endl;
    cout<<"5. Day Cycle Frequency"<<endl;
    cout<<"6. Frequency of Repeatation"<<endl;
    cin>>index;
    switch(index){
        case 1:
            EditFile(1,username);
            break;
        case 2:
            EditFile(2,username);
            break;
        case 3:
            EditFile(3,username);
            break;
        case 4:
            EditFile(4,username);
            break;
        case 5:
            EditFile(5,username);
            break;
        case 6:
            EditFile(6,username);
            break;       
        default:
            cout<<"Wrong choice. Please enter again"<<endl;
            edit(username); 
            break;   
    }
}

int main()
{
    return 0;
}