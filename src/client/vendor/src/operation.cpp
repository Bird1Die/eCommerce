#include "main.h"

int AddInsertion(Context ctx, string name, float price){
    redisReply *reply = RedisCommand(ctx.GetRedis(), 
    "XADD vendor * operation_id 2 product_name %s price %f id_vendor %s", name, price, ctx.GetId());

    string rid = reply->str;
    return 0;
}