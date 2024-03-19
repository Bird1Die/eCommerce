#include "main.h"

/*
analyzes the message extracting the necessary informations that will be used to add
the new customer into the database. It sends a message to the new customer whit their id.
*/
int newRegistrationMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string username = single_entry->element[1]->element[3]->str;
    string email = single_entry->element[1]->element[5]->str;
    string password = single_entry->element[1]->element[7]->str;
    string shipping_address = single_entry->element[1]->element[9]->str;

    replace(shipping_address.begin(), shipping_address.end(), '_', ' ');
    system("clear");
    
    int id_customer = newRegistrationDB(username, email, password, shipping_address); 
    if (id_customer < 0) {
        cout << "Error creating new customer" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
    cout << "New customer created with id: " << id_customer << ", username: " << username << ", email: " << email << endl;
    messageReturnIdRedis(redis, entry_number, id_customer);
    return 0; 

}

/*
analyzes the message extracting the necessary informations that will be used to add a new 
order into the database. A message is sent to the redis customer client to confirm the successful 
operation and to the transporter to create a new shipping.
*/
int newOrderMsg(redisReply *reply, redisContext *redis) {
    redisReply *prima_reply = reply->element[0];
    redisReply *single_entry = prima_reply->element[1]->element[0];
    string entry_number = single_entry->element[0]->str;
    string id_product = single_entry->element[1]->element[3]->str;
    string quantity = single_entry->element[1]->element[5]->str;
    string id_customer = single_entry->element[1]->element[7]->str;

    system("clear");
    int id_order = newOrderDB(id_product, quantity, id_customer);

    if (id_order < 0) {
        cout << "Error creating new order" << endl;
        statusErrMessageRedis(redis, entry_number);
        return -1;
    } else {
        cout << "Order created with id: " << id_order << ", quantity: " << quantity << ", id_customer: " << id_customer  << ". Sendig message to the customer..." << endl;
        messageStatusOkRedis(redis, entry_number);
        //da correggere con l'id del trasportatore disponibile (non occupato in altre consegne)
        messageToTransporter(redis, id_order);
       return 0; 
    }
}

/*
analyzes the message extracting the necessary informations that will be used to search
user credentials inside the database. A message is sent to the redis customer client to 
confirm the seccussful operation including the customer's id.
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
        cout << "Successful operatio." << endl;
        cout << "Sending message to entry: " << entry_number << " with ID: " << id << endl;
        messageReturnIdRedis(redis, entry_number, id);
        return 0; 
    } else {
        cout << "Error login" << endl;
        cout << "Sending message to entry: " << entry_number << " with negative result";
        statusErrMessageRedis(redis, entry_number);
        return -1;
    }
}