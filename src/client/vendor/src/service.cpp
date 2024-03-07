#include "main.h"

int AuthenticationService(Context ctx){
    bool run = true;
    vector<string> keywords = {"Registration", "Login", "Exit"};
    Kwd_Man kwd = Kwd_Man(keywords);
    int flag = -2;
    while(run){
        //system("clear");
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
        //system("clear");
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
    return 0;
}

int VisualizeInsertion(Context ctx){
    return 0;
}