#include "main.h"

int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser) {
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 1 iduser %d", id_entry.c_str(), iduser);
    return 0;
}

int statusErrMessageRedis(redisContext *redis, string id_entry) {
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 2", id_entry.c_str());
    return 0;
}

int messageStatusOkRedis(redisContext *redis, string id_entry) {
    sleep(1);
    redisCommand(redis, "XADD %s * operation_id 3", id_entry.c_str());
    return 0;
}

int messageToTransporter(redisContext *redis, int idorder) {
    sleep(1);
    cout << "Sending message to transporter" << endl;
    redisCommand(redis, "XADD transporter * operation_id 3 id_order %d", idorder);
    return 0;
}