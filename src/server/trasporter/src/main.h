#include <iostream>
#include <hiredis/hiredis.h>
#include <../../../../con2db/pgsql.h>
#include <../../../../con2redis/src/con2redis.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unistd.h>
using namespace std;

int main();

//database
Con2DB CreateDB();
int newRegistrationDB(string username, string email, string password);
int newShippingDB(string id_order);
int queryShippingToTransporter();
int loginDB(string username, string password);
int requestShippingDB(int id_transporter);

//operation
int newRegistrationMsg(redisReply *reply, redisContext *redis);
//int newShippingMsg(redisReply *reply, redisContext *redis);
int loginMsg(redisReply *reply, redisContext *redis);
int requestShippingMsg(redisReply *reply, redisContext *redis);

//utils
int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser);
int statusErrMessageRedis(redisContext *redis, string id_entry);
int messageStatusOkRedis(redisContext *redis, string id_entry);