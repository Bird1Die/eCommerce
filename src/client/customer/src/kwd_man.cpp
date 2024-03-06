#include "main.h"

Kwd_Man::Kwd_Man(vector<string> keywords){this->keywords = keywords;}
string Kwd_Man::ToString(){
    string str;
    for(int i = 0; i < this->keywords.size(); i++){
        str.append(to_string(i+1));
        str.append(". ");
        str.append(this->keywords[i]);
        str.append("\t");
    }
    return str;
}