#include "main.h"

void Notification(string message){
    system("clear");
    cout << message << flush;
    sleep(1);
}

bool StringIsNumerical(string s){
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

bool StringIsInLenght(string str, int min, int max){
    return (str.length() >= min) && (str.length() <= max);
}

redisReply* GetFirstEntry(redisReply *reply){
    return reply->element[0]->element[1]->element[0];
}

redisReply* GetFirstEntryElements(redisReply *reply){
    return reply->element[0]->element[1]->element[0]->element[1];
}
// Context

Context::Context(Con2DB db, redisContext *redis){
    this->db = db;
    this->redis = redis;
}

redisContext* Context::GetRedis(){
    return this->redis;
}

int Context::GetId(){
    return this->id;
}

Con2DB Context::GetDB(){
    return this->db;
}

void Context::SetId(int id){
    this->id = id;
}

// Insertion

Insertion::Insertion(int id, string name, float price, int sales){
    this->id = id;
    this->name = name;
    this->price = price;
    this->sales = sales;
}
string Insertion::GetName(){return this->name;}
float Insertion::GetPrice(){return this->price;}
int Insertion::GetId(){return this->id;}
int Insertion::GetSales(){return this->sales;}