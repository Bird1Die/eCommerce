#include "main.h"
#include <unistd.h>

/*
redis server listening requests from redis vendor client.
*/
int main(){
    redisContext *redis = redisConnect("localhost", 6379);
    system("clear");
    bool run = true;
    while(run) {
        redisReply *reply = (redisReply*) redisCommand(redis, "XRANGE transporter - + COUNT 1");
        if (reply->elements != 0){
            redisReply *prima_reply = reply->element[0];
            string id_entry = prima_reply->element[0]->str;
            string operation_id = prima_reply->element[1]->element[1]->str;  
            // XADD vendor * operation_id 1 username %s password %s email %s"
            switch (stoi(operation_id))
                {
                case 1: 
                    cout << "Registrazione" << endl;
                    newRegistrationMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, prima_reply->element[1]->element[7]->str, redis);
                    break;
                case 2:
                    cout << "New Insertion" << endl;
                    newInsertionMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, prima_reply->element[1]->element[7]->str, redis);
                    break;
                case 3: 
                    cout << "Login" << endl;   
                    loginMsg(id_entry, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, redis); 
                    break;
                }
                redisCommand(redis, "XDEL vendor %s", id_entry.c_str());
            }
    } 
    
    return 0;
}