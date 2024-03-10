#include "main.h"

int AuthenticationService(Context ctx){
    bool run = true;
    vector<string> keywords = {"Registration", "Login", "Exit"};
    Kwd_Man kwd = Kwd_Man(keywords);
    int flag = -2;
    while(run){
        system("clear");
        cout << kwd.ToString() << endl;

        string comand;
        getline(cin, comand);

        flag = ManageAuthenticationKwd(ctx, comand);
        if(flag == -1){
            run = false;
        }
        if(flag >= 0){
            break;
        }
    }
    return flag;
}

int MainService(Context ctx){
    bool run = true;
    vector<string> keywords = {"Create insertion", "Visualize insertions", "Exit"};
    Kwd_Man kwm = Kwd_Man(keywords);
    while(run){
        system("clear");
        cout << kwm.ToString() << endl;

        string comand; 
        getline(cin, comand);

        int flag = ManageMainKwd(ctx, comand);

        if(flag == -1){
            run = false;
            break;
        }
    }
    return 0;
}

int CreateInsertion(Context ctx){
    bool run = true;
    system("clear");

    cout << "Insert product name: ";
    string name;
    getline(cin, name);

    if(!StringIsInLenght(name, 2, 50)){
        Notification("Name lenght is out of range [2, 50]");
        return 0;
    }

    cout << "Insert product price: ";
    string price_str;
    getline(cin, price_str);

    float price;
    try{
        price = stof(price_str);
    } catch(exception e){
        Notification("Invalid price");
        return 0;
    }
    float tronc = round(price * pow(10, 2)) / pow(10, 2);

    system("clear");
    cout << "Recap product" << endl << endl;
    cout << "Name: " << name << endl;
    cout << "Price: " << tronc << "$" << endl << endl;
    cout << "Add this insertion? (Y/n)" << endl;

    string comand;
    getline(cin, comand);
    if(comand.length() > 1 || comand.length() < 1){
        Notification("Invalid input");
        return 0;
    }
    cout << "1" << endl;
    char com = tolower(comand.c_str()[0]);
    cout << "2" << endl;
    if(com == 'y'){
        cout << "3" << endl;
        int flag = AddInsertion(ctx, name, tronc);
        if(flag == 0){
            Notification("Correctly created the insertion");
            return 0;
        }
        else{
            Notification("Error in database while creating the insertion");
            return 0;
        }
    }
    else if(com == 'n'){
        Notification("Cancello il prodotto");
    }
    else{
        Notification("Invalid input");
        return 0;
    }
    return 0;
}

int VisualizeInsertion(Context ctx){
    vector<Insertion> insertions = GetInsertion(ctx);
    system("clear");
    cout << "Your insertions" << endl << endl;
    for(int i = 0; i < insertions.size(); i++){
        Insertion ins = insertions[i];
        cout << "Name: " << ins.GetName() << " Price: " << ins.GetPrice() << " Sales: " << ins.GetSales() << endl;
    }
    string comand;
    getline(cin, comand);
}