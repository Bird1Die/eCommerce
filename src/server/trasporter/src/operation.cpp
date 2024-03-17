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
    
    system("clear");
    int id_vendor = newRegistrationDB(username, email, password); 
    if (id_vendor < 0) {
        cout << "error creating new transport" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "New transporter created with id " << id_vendor << endl;
    messageReturnIdRedis(redis, entry_number, id_vendor);
    return 0; 

}

/*

*/
int requestShippingMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string id_transporter = single_entry->element[1]->element[3]->str;

    int status = requestShippingDB(stoi(id_transporter));
    system("clear");
    if (status == -2) {
        cout << "Nessun ordine disponibile" << endl;
        messageNoOrderAvailable(redis, entry_number);
        return -1;
    } else if (status == -1) {
        cout << "Error query" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "New shipping created" << endl;
    messageStatusOkRedis(redis, entry_number);
    return 0;
}

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
    system("clear");
    int id = loginDB(username, password);
    if (id != -1) {
        cout << "Login transporter with id " << id << endl;
        messageReturnIdRedis(redis, entry_number, id);
        return 0; 
    } else {
        cout << "Error login" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
}

/*

*/
int changeShippingStatusMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string id_shipping = single_entry->element[1]->element[3]->str;
    string sh_status = single_entry->element[1]->element[5]->str;
    system("clear");

    int status = changeShippingStatusDB(stoi(id_shipping), sh_status);
    if (status < 0) {
        cout << "Error update shipping status" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "shipping status correctly updated" << endl;
    messageStatusOkRedis(redis,entry_number);
    return 0;
}