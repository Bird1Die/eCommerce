#include "main.h"

int main(){
    Context ctx = Context();
    bool run = true;
    vector<string> keywords = {"Registration", "Login", "Exit"};
    Kwd_Man kwd = Kwd_Man(keywords);
    while(run){
        system("clear");
        cout << kwd.ToString() << endl;

        string comand;
        getline(cin, comand);

        int flag = ManageAuthenticationKwd(ctx, comand);
        if(flag == -1){
            run = false;
        }
    }
    return 0;
}