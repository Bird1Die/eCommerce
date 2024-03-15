#include "main.h"

/*
analyzes the message extracting the necessary informations that will be used to add
the new transporter into the database. It sends a message to the new vendor whit their id.
*/
int newRegistrationMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string username = single_entry->element[1]->element[3]->str;
    string email = single_entry->element[1]->element[5]->str;
    string password = single_entry->element[1]->element[7]->str;
    cout << "Entry: " << entry_number << ", username: " << username << ", email: " << email << ", password: " << password << endl;
    
    int id_vendor = newRegistrationDB(username, email, password); 
    if (id_vendor < 0) {
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    messageReturnIdRedis(redis, entry_number, id_vendor);
    return 0; 

}

int requestShippingMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string id_transporter = single_entry->element[1]->element[3]->str;

    int id_order = requestShippingDB(stoi(id_transporter));
    
}

/*
analyzes the message extracting the necessary informations that will be used to add
the new shipping into the database. 

int newShippingMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string id_order = single_entry->element[1]->element[3]->str;

    cout << "id_order: " << id_order << endl;
    int status = newShippingDB(id_order);
    if (status < 0) {
        //rimando il messaggio al server stesso per riprovare??
    } else {
        //devo mandare un messaggio a qualcuno??
    }

}
*/

/*
analyzes the message extracting the necessary informations that will be used to search
user credentials inside the database. A message is sent to the redis transporter client to 
confirm the seccussful operation including the transporter's id.
*/
int loginMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string username = single_entry->element[1]->element[3]->str;
    string password = single_entry->element[1]->element[5]->str;

    int id = loginDB(username, password);
    if (id != -1) {
        cout << "Sending message to entry: " << entry_number << " with ID: " << id << endl;
        messageReturnIdRedis(redis, entry_number, id);
        return 0; 
    } else {
        cout << "Sending message to entry: " << entry_number << " with negative result";
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
}