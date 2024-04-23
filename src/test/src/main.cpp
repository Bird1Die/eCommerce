#include "main.h"

int main(){
    srand(time(0));
    system("clear");
    redisContext *redis = redisConnect("localhost", 6379);

    // Vendor test

    cout << "Vendor registration test:" << endl;
    sleep(1);
    vector<int> vendorIds = VendorRegistation(redis);

    cout << endl << endl << "Vendor create insertion test: " << endl;
    sleep(1);
    VendorCreateInsertion(redis, vendorIds);

    // Customer test
    
    cout << endl << endl << "Customer registration test:" << endl;
    vector<int> customerIds = CustomerRegistation(redis);

    return 0;
}