#include <hiredis/hiredis.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <../../../../con2db/pgsql.h>

using namespace std;

int main();

// Context

class Context{
    private:
        int id;
        Con2DB db;
    public:
        Context(Con2DB db);
        Con2DB GetDB();
        int GetId();
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
int ManageMainKwd(Context ctx, string comand);

// Service

int AuthenticationService(Context ctx);
int MainService(Context ctx);
int CreateInsertion(Context ctx);
int VisualizeInsertion(Context ctx);

// Authentication

int Registration(Context ctx);
int Login(Context ctx);

// Util

void Notification(string message);
bool StringIsNumerical(string str);