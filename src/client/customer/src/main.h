#include <hiredis/hiredis.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <../../../../con2db/pgsql.h>
#include <../../../../con2redis/src/con2redis.h>

using namespace std;

int main();

// Context

class Context{
    private:
        bool debug;
        int id;
        Con2DB db;
        redisContext *redis;
    public:
        Context(Con2DB db, redisContext *redis);
        bool GetDebug();
        void SetDebug(bool debug);
        redisContext *GetRedis();
        Con2DB GetDB();
        int GetId();
        void SetId(int id);
};

// Keywords

class Kwd_Man{
private:
    vector<string> keywords;
public:
    Kwd_Man(vector<string>);
    string ToString();
};

// Insertion

class Insertion{
private:
    int id;
    string name;
    float price;
    int sales;
public:
    Insertion(int id, string name, float price, int sales);
    string GetName();
    float GetPrice();
    int GetId();
    int GetSales();
};

int ManageAuthenticationKwd(Context ctx, string comand);
int ManageMainKwd(Context ctx, string comand);

// Service

int AuthenticationService(Context ctx);
int MainService(Context ctx);
int SearchProduct(Context ctx);
int VisualizeOrders(Context ctx);

// Operation

vector<Insertion> GetProductList(Context ctx, string name);
vector<Insertion> GetOrderList(Context ctx);

// Authentication

int Registration(Context ctx);
int Login(Context ctx);

// Util

void Notification(string message);
bool StringIsNumerical(string str);
bool StringIsInLenght(string str, int min, int max);
redisReply* GetFirstEntry(redisReply *reply);
redisReply* GetFirstEntryElements(redisReply *reply);