#include "main.h"

int main(){
    srand(time(0));
    redisContext *redis = redisConnect("localhost", 6379);

    vector<int> vendorIds = VendorRegistation(redis);
    for(int i = 0; i < vendorIds.size(); i++){
        cout << "Index: " << i << " Value: " << vendorIds.at(i) << endl;
    }
    vector<int> productIds = VendorCreateInsertions(redis, vendorIds);

    return 0;
}