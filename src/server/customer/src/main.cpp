#include "main.h"

/*
redis server listening requests from redis customer client.
*/
int main() {
    redisContext *redis = redisConnect("localhost", 6379);
    bool run = true;
    while(run) {
        system("clear");
        redisReply *reply = (redisReply*) redisCommand(redis, "XRANGE customer - + COUNT 1");
        if (reply->elements != 0){
            redisReply *prima_reply = reply->element[0];
            string id_entry = prima_reply->element[0]->str;
            string operation_id = prima_reply->element[1]->element[1]->str;
            switch (stoi(operation_id))
                {
                case 1: 
                    cout << "Registrazione" << endl;
                    newRegistrationMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, prima_reply->element[1]->element[7]->str, prima_reply->element[1]->element[9]->str, redis);
                    break;
                case 2:
                    cout << "New Order" << endl;
                    newOrderMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, prima_reply->element[1]->element[7]->str, redis);
                    break;
                case 3: 
                    cout << "Login" << endl;   
                    loginMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, redis); 
                    break;
                }
            redisCommand(redis, "XDEL customer %s", id_entry.c_str());
        }
    } 
    return 0;
}