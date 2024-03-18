#include "main.h"

int AuthenticationService(Context ctx){
    bool run = true;
    vector<string> keywords = {"Registration", "Login", "Exit"};
    Kwd_Man kwd = Kwd_Man(keywords);
    int flag;
    while(run){
        int comand = kwd.GetComandId();
        flag = ManageAuthenticationKwd(ctx, comand);
        if(flag == -1){run = false;}
        if(flag >= 0){break;}
    }
    return flag;
}