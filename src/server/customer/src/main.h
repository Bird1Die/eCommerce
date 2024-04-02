#include <iostream>
#include <hiredis/hiredis.h>
#include <../../../../con2db/pgsql.h>
#include <../../../../con2redis/src/con2redis.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <thread>
using namespace std;

int main();

// database
Con2DB CreateDB();
int newRegistrationDB(string username, string email, string password, string shipping_address);
int newOrderDB(string id_product, string quantity, string id_customer);
int loginDB(string email, string password);

// operation
int newRegistrationMsg(redisReply *reply, redisContext *redis);
int newOrderMsg(redisReply *reply, redisContext *redis);
int loginMsg(redisReply *reply, redisContext *redis);

// utils
int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser);
int statusErrMessageRedis(redisContext *redis, string id_entry);
int messageStatusOkRedis(redisContext *redis, string id_entry);
int messageToTransporter(redisContext *redis, int idorder);


// thread
void manageThread(string operation, redisReply *reply, redisContext *redis);