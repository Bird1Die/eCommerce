#include "main.h"

/*
analyzes the message extracting the necessary informations that will be used to add
the new vendor into the database. It sends a message to the new vendor whit their id.
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
        cout << "Error registartion new vendor." << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "New vendor created with id: " << id_vendor << ", username: " << username << ", email: " << email << ", password: " << password << endl;
    messageReturnIdRedis(redis, entry_number, id_vendor);
    return 0; 

}

/*
analyzes the message extracting the necessary informations that will be used to add a new 
insertion into the database. A message is sent to the redis vendor client to confirm the successful 
operation.
*/
int newInsertionMsg(redisReply *reply, redisContext *redis) {
    //"XADD vendor * operation_id 2 product_name %s price %s id_vendor %s"
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string product_name = single_entry->element[1]->element[3]->str;
    string price = single_entry->element[1]->element[5]->str;
    string id_vendor = single_entry->element[1]->element[7]->str;

    replace(product_name.begin(), product_name.end(), '_', ' ');
    cout << "Entry: " << entry_number << ", product_name: " << product_name << ", price: " << price << ", id_vendor: " << id_vendor << endl;
    
    int status = newInsertionDB(product_name, price, id_vendor);

    if (status != 0) {
        statusErrMessageRedis(redis, entry_number);
        return -1;
    } else {
        messageStatusOkRedis(redis, entry_number);
       return 0; 
    }
}

/*
analyzes the message extracting the necessary informations that will be used to search
user credentials inside the database. A message is sent to the redis vendor client to 
confirm the seccussful operation including the vendor's id.
*/
int loginMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string email = single_entry->element[1]->element[3]->str;
    string password = single_entry->element[1]->element[5]->str;

    int id = loginDB(email, password);
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