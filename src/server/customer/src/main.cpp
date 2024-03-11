#include "main.h"

int main() {
    redisContext *redis = redisConnect("localhost", 6379);
    system("clear");
    bool run = true;
    while(run) {
       redisReply *reply = (redisReply*) redisCommand(redis, "XREAD COUNT 1 BLOCK 10000 STREAMS customer $");
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
                cout << "New Order" << endl;
                newOrderMsg(reply, redis);
                break;
            case 3: 
                cout << "Login" << endl;   
                //loginMsg(reply, redis); 
                break;
            }
        }
    } 
    
    return 0;
}