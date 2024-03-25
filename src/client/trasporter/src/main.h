#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <termios.h>
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

class Shipping{
private:
    int id;
    string customer_name;
    string shipping_address;
    string product_name;
    int quantity;
    string status;
public:
    Shipping(int id, string customer_name, string shipping_address, string product_name, int quantity, string status);
    int GetId();
    string GetShippingAddress();
    string GetProductName();
    int GetQuantity();
    string GetStatus();
    void SetStatus(string status);
    string ToString();
};

// Authentication

int Registration(Context ctx);
int Login(Context ctx);

// Service

int AuthenticationService(Context ctx);
int MainService(Context ctx);
int NewShipping(Context ctx);
int MyShippings(Context ctx);

// Operation

int NewShippingOrder(Context ctx);
vector<Shipping> GetShippings(Context ctx);

// Manage keyword

int ManageAuthenticationKwd(Context ctx, int comand);
int ManageMainKwd(Context ctx, int comand);

class Kwd_Man{
private:
    vector<string> keywords;
    long unsigned int selected;
public:
    Kwd_Man(vector<string> keywords);
    string ToString();
    void Previous();
    void Next();
    int GetSelected();
    int GetComandId();
    int GetComandId(string msg);
};



// Util

void Notification(string message);
redisReply* GetFirstEntry(redisReply *reply);
redisReply* GetFirstEntryElements(redisReply *reply);
char getch();