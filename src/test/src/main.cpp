#include "main.h"

int main(){
    redisContext *redis = redisConnect("localhost", 6379);
    CustomerRegistation(redis);
    return 0;
}

void signalHandler(int signum){
    cout << "Signal: " << signum << endl << flush;
    exit(0);
}