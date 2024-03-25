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

int MainService(Context ctx){
    bool run = true;
    Kwd_Man kwd = Kwd_Man({"New shipping", "My shippings", "Exit"});
    int flag;
    while(run){
        int comand = kwd.GetComandId();
        flag = ManageMainKwd(ctx, comand);
        if(flag == -1){return 0;}
    }
}

int NewShipping(Context ctx){
    Kwd_Man kwm = Kwd_Man({"Yes", "No"});
    int comand = kwm.GetComandId("Confirm new order\n\n");
    if(!comand){
        system("clear");
        bool flag = NewShippingOrder(ctx);
        if(!flag){cout << "Correctly got and order" << endl;}
        else{cout << "No orders available" << endl;}
    }
    return 0;
}

int MyShippings(Context ctx){ 
    vector<Shipping> shippings = GetShippings(ctx);
    for(int i = 0; i < shippings.size(); i++){
        
    }
}