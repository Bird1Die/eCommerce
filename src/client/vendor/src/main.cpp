#include "main.h"

int main(){
    Con2DB db = Con2DB();
    Context ctx = Context(db);
    
    bool run = true;
    int flag;
    while(run){
        flag = AuthenticationService(ctx);
        if(flag == -1){
            run = false;
            break;
        }
        if(flag >= 0){
            break;
        }
    }
    
    // Main cycle
    while(run){
        flag = MainService(ctx);
    }

    return 0;
}