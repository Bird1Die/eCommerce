#include <hiredis/hiredis.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <algorithm>
using namespace std;

int main();

// Context

class Context{
    private:
    public:
        Context();
};

// Keywords

class Kwd_Man{
private:
    vector<string> keywords;
public:
    Kwd_Man(vector<string>);
    string ToString();
};

int ManageAuthenticationKwd(Context ctx, string comand);

// Service

int Registration(Context ctx);
int Login(Context ctx);

// Util

void Notification(string message);
bool StringIsNumerical(string str);