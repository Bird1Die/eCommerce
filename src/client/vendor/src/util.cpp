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