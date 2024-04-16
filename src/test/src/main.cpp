#include "main.h"

int main(){
    srand(time(0));
    redisContext *redis = redisConnect("localhost", 6379);

    VendorRegistation(redis);

    return 0;
}