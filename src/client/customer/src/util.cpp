#include "main.h"

void Notification(string message){
    system("clear");
    cout << message << flush;
    sleep(1);
}

bool StringIsNumerical(string s){
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

// Context

Context::Context(){

}