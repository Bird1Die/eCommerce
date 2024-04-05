#include "main.h"

/*
analyzes the message extracting the necessary informations that will be used to add
the new transporter into the database. It sends a message to the new vendor whit their id.
*/
int newRegistrationMsg(string entry_number, string username, string email, string password, redisContext *redis) {
    /*
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string username = single_entry->element[1]->element[3]->str;
    string email = single_entry->element[1]->element[5]->str;
    string password = single_entry->element[1]->element[7]->str;
    */
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
analyzes the message extracitng the information for the request shipping.
If there is an order available for shipping, then the shipping is created and a message is sent to 
the transporte who did the request. Otherwise it returns an error message.
*/
int requestShippingMsg(string entry_number, string id_transporter, redisContext *redis) {
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
int loginMsg(string entry_number, string username, string password, redisContext *redis) {
    int id = loginDB(username, password);
    if (id != -1) {
        cout << "Login transporter with id " << id << endl;
        messageReturnIdRedis(redis, entry_number, id);
        cout << "ho mandato il messaggio" << endl;
        return 0; 
    } else {
        cout << "Error login" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
}

/*
analyzes the message extracting the necessary informations that will be used to change the 
shipping status. A message is sent to the redis transporter client to confirm the 
successful operation or the error.
*/
int changeShippingStatusMsg(string entry_number, string id_shipping, string sh_status, redisContext *redis) {
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