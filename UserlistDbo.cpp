#include <bits/stdc++.h>
using namespace std;

void signup(string &username){
    string name, passwd, c_passwd, entry;
    cout << "Enter your name: \n";
    cin >> name;
    cout << "Enter your password: \n";
    cin >> passwd;
    cout << "Confirm your password: \n";
    cin >> c_passwd;
    for(int i = 0; i < 3; i++){
        if(c_passwd != passwd){
            cout << "Passwords do not match.\n";
            cout << "Confirm your password: \n";
            cin >> c_passwd;
            if(c_passwd == passwd){
                break;
            }
        }
    }
    fstream fout;
    fout.open("userlist.csv", ios::out | ios::app);
    entry = username + "," + name + "," + passwd + "\n";
    fout << entry;
    fout.close();
}

void login(string &username){
    ifstream fin("userlist.csv");
    vector<string> row;
    string line, word, pass;
    int count = 0;
    while(getline(fin, line)){
        row.clear();
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        if(username == row[0]){
            count = 1;
            cout << "Enter your password: \n";
            cin >> pass;
            for(int i = 0; i < 3; i++){
                if(pass == row[2]){
                    cout << "Login successful.\n";
                    break;
                }
                else{
                    cout << "Incorrect password.\n";
                    cout << "Enter your password: \n";
                    cin >> pass;

                }
            }
        }
    }
    if(count = 0){
        cout << "Username does not exist. Please login.\n";
        signup(username);
    }
    fin.close();
}

void change_pass(string &username){
    fstream fin, fout;
    fin.open("userlist.csv", ios::in);
    fout.open("userlistnew.csv", ios::out);
    string line, word;
    vector<string> row;
    string newpass, pass;
    while(!fin.eof()){
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
        int row_size = row.size();
        if(username == row[0]){
            cout << "Enter previous password:\n";
            cin >> pass;
            for(int i = 0; i < 3; i++){
                if(pass == row[2]){
                    cout << "Enter new password:\n";
                    cin >> newpass;
                    break;
                }
                else{
                    cout << "Previous password is incorrect.\n";
                    cout << "Enter previous password.\n";
                    cin >> pass;
                }
            }
            stringstream c;
            c << newpass;
            row[2] = c.str();
            if(!fin.eof()){
                for(int i = 0; i < row_size-1; i++){
                    fout << row[i] << ",";
                }
                fout << row[row_size-1] << "\n";
            }
        }
        else{
            if(!fin.eof()){
                for(int i = 0; i < row_size-1; i++){
                    fout << row[i] << ",";
                }
                fout << row[row_size-1] << "\n";
            }
        }
        if(fin.eof()){
            break;
        }
    }
    fin.close();
    fout.close();
    remove("userlist.csv");
    rename("userlistnew.csv", "userlist.csv");
}