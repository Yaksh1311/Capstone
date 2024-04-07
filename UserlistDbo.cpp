#include <bits/stdc++.h>
#include "UserlistDBO.hpp"

void signup(std::string username){
    std::string name, passwd, c_passwd, entry;
    std::cout << "Enter your name: \n";
    std::cin >> name;
    std::cout << "Enter your password: \n";
    std::cin >> passwd;
    std::cout << "Confirm your password: \n";
    std::cin >> c_passwd;
    for(int i = 0; i < 3; i++){
        if(c_passwd != passwd){
            std::cout << "Passwords do not match.\n";
            std::cout << "Confirm your password: \n";
            std::cin >> c_passwd;
            if(c_passwd == passwd){
                break;
            }
        }
    }
    std::fstream fout;
    fout.open("userlist.csv", std::ios::out | std::ios::app);
    entry = username + "," + name + "," + passwd + "\n";
    fout << entry;
    fout.close();
}

void login(std::string username){
    std::ifstream fin("userlist.csv");
    std::vector<std::string> row;
    std::string line, word, pass;
    int count = 0;
    while(getline(fin, line)){
        row.clear();
        std::stringstream s(line);
        while(std::getline(s, word, ',')){
            row.push_back(word);
        }
        if(username == row[0]){
            count = 1;
            std::cout << "Enter your password: \n";
            std::cin >> pass;
            for(int i = 0; i < 3; i++){
                if(pass == row[2]){
                    std::cout << "Login successful.\n";
                    break;
                }
                else{
                    std::cout << "Incorrect password.\n";
                    std::cout << "Enter your password: \n";
                    std::cin >> pass;
                }
            }
        }
    }
    if(count = 0){
        std::cout << "Username does not exist. Please signup.\n";
        signup(username);
    }
    fin.close();
}

void change_pass(std::string username){
    std::fstream fin, fout;
    fin.open("userlist.csv", std::ios::in);
    fout.open("userlistnew.csv", std::ios::out);
    std::string line, word;
    std::vector<std::string> row;
    std::string newpass, pass;
    while(!fin.eof()){
        row.clear();
        std::getline(fin, line);
        std::stringstream s(line);
        while(std::getline(s, word, ',')){
            row.push_back(word);
        }
        int row_size = row.size();
        if(username == row[0]){
            std::cout << "Enter previous password:\n";
            std::cin >> pass;
            for(int i = 0; i < 3; i++){
                if(pass == row[2]){
                    std::cout << "Enter new password:\n";
                    std::cin >> newpass;
                    break;
                }
                else{
                    std::cout << "Previous password is incorrect.\n";
                    std::cout << "Enter previous password.\n";
                    std::cin >> pass;
                }
            }
            std::stringstream c;
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