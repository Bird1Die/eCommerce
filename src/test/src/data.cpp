#include "main.h"

vector<string> GetVendorUsernameData(int NTEST){
    vector<string> vec;
    vector<string> data;
    ifstream file("../data/VendorUsername.txt");
    if(!file.is_open()){cerr << "Impossibile aprire il file" << endl; return vec;}
    string line;
    while(getline(file, line)){
        vec.push_back(line);
    }

    size_t veclen = vec.size();
    string username;
    for(int i = 0; i < NTEST; i++){
        if(vec.size() == 0){data.push_back("OutOfTests");}
        username.clear();
        username = vec.at(rand() % veclen);
        data.push_back(username); 
        auto it = find(vec.begin(), vec.end(), username);
        vec.erase(it);
        veclen = vec.size();
    }

    return data;
}

vector<string> GetVendorPasswordData(int NTEST){
    vector<string> vec;
    string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charsetlen = charset.length();
    int passlen = 8;

    srand(time(0));

    string pass;

    for(int i = 0; i < NTEST ; i++){
        for(int j = 0; j < passlen; j++){
            pass += charset[rand() % charsetlen];
        }
        vec.push_back(pass);
        pass.clear();
    }

    return vec;
}

string GetVendorEmailData(string name){
    string charset = "0123456789";
    size_t charsetlen = charset.length();    
    string email = name;
    int len = 2;

    email += ".";
    for(int i = 0; i < len; i++){
        email += charset[rand() % charsetlen];
    }
    email += "@gmail.com";
    return email;
}

vector<string> GetVendorProductNameData(int NTEST){
    vector<string> vec;
    vector<string> data;
    ifstream file("../data/VendorProductName.txt");
    if(!file.is_open()){cerr << "Impossibile aprire il file" << endl; return vec;}
    string line;
    while(getline(file, line)){
        vec.push_back(line);
    }
    
        size_t veclen = vec.size();
    string username;
    for(int i = 0; i < NTEST; i++){
        if(vec.size() == 0){data.push_back("OutOfTests");}
        username.clear();
        username = vec.at(rand() % veclen);
        data.push_back(username); 
        auto it = find(vec.begin(), vec.end(), username);
        vec.erase(it);
        veclen = vec.size();
    }

    return data;
}