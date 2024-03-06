#include "main.h"

int ManageAuthenticationKwd(Context ctx, string comand){
    int n = StringIsNumerical(comand) ? atoi(comand.c_str()) : 0;
    switch (n)
    {
    case 1:
        Registration(ctx);
        return 0;
    case 2:
        Login(ctx);
        return 0;
    case 3:
        return -1;
    default:
        Notification("Invalid token");
        return 0;
    }
    return 0;
    
}

Kwd_Man::Kwd_Man(vector<string> keywords){this->keywords = keywords;}
string Kwd_Man::ToString(){
    string str;
    for(int i = 0; i < this->keywords.size(); i++){
        str.append(this->keywords[i]);
        str.append(" (");
        str.append(to_string(i+1));
        str.append(")");
        str.append(" | ");
    }
    return str;
}