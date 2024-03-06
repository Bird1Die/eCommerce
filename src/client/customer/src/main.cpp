#include "main.h"

int main(){
    bool run = true;
    vector<string> keywords = {"Ciao", "Exit"};
    Kwd_Man kwd = Kwd_Man(keywords);
    while(run){
        cout << kwd.ToString();
    }
    return 0;
}