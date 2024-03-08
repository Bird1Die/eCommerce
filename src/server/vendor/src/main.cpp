#include "main.h"
#include <unistd.h>

int main(){
    redisContext *redis = redisConnect("localhost", 6379);
    bool run = true;
    while(run) {
       redisReply *reply = (redisReply*) redisCommand(redis, "XREAD COUNT 1 BLOCK 10000 STREAMS vendor $");
        if (reply->elements != 0){
        redisReply *prima_reply = reply->element[0];
        cout << "Stream name: " << prima_reply->element[0]->str << endl;
        redisReply *single_entry = prima_reply->element[1]->element[0];
        string entry_number = single_entry->element[0]->str;
        string operation_id = single_entry->element[1]->element[1]->str;
        cout << "Entry: " << entry_number << ", operationID: " << operation_id << endl; 
        switch (stoi(operation_id))
            {
            case 1: 
                cout << "Registrazione" << endl;
                newRegistrationMsg(reply, redis);
                break;
            case 2:
                cout << "New Insertion" << endl;
                newInsertionMsg(reply, redis);
                break;
            case 3: 
                cout << "Login" << endl;    
                break;
            }
        }
    } 
    
    return 0;
}