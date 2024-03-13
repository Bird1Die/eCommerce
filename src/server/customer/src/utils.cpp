#include "main.h"

/*
message to redis customer client to confirm that a new customer was created with the given id. 
The channel ID from which the messsage was received is used.
*/
int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser) {
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 1 iduser %d", id_entry.c_str(), iduser);
    return 0;
}

/*
message to redis customer client to inform that there has been an error.
The channel ID from which the message was received is used.
*/
int statusErrMessageRedis(redisContext *redis, string id_entry) {
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 2", id_entry.c_str());
    return 0;
}

/*
message to redis customer client to confirm the successful ooperation.
The channel ID from which the message was received is used.
*/
int messageStatusOkRedis(redisContext *redis, string id_entry) {
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 3", id_entry.c_str());
    return 0;
}

/*
message to redis transporter client to inform that a new order was created with the given id.
*/
int messageToTransporter(redisContext *redis, int idorder) {
    sleep(1);
    cout << "Sending message to transporter" << endl;
    redisCommand(redis, "XADD transporter * operation_id 4 id_order %d", idorder);
    return 0;
}