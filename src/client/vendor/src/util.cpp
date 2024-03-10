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

// Insertion

Insertion::Insertion(string name, float price){
    this->name = name;
    this->price = price;
}

string Insertion::GetName(){
    return this->name;
}

float Insertion::GetPrice(){
    return this->price;
}