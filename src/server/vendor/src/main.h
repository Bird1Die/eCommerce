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
int newInsertionDB(string product_name, string price, string id_vendor);
int loginDB(string email, string password);

//operation
int newRegistrationMsg(redisReply *reply, redisContext *redis);
int newInsertionMsg(redisReply *reply, redisContext *redis);
int loginMsg(redisReply *reply, redisContext *redis); 

//utils
bool isNumerical(string str);
bool isIntNumerical(string str);
int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser);
int statusErrMessageRedis(redisContext *redis, string id_entry);
int messageStatusOkRedis(redisContext *redis, string id_entry);