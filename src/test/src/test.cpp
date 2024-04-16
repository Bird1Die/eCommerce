#include "main.h"

vector<int> VendorRegistation(redisContext *redis){
    vector<int> vendorIds;
    vector<string> CustomerUsernames = GetVendorUsernameData(NTEST);
    vector<string> CustomerPasswords = GetVendorPasswordData(NTEST);
    for(int i = 0; i < NTEST; i++){
        cout << "Test n." << i + 1 << "\t";
        string username = CustomerUsernames.at(i);
        cout << "Username: " << username << ";\t";
        string password = CustomerPasswords.at(i);
        cout << "Password: " << password << ";\t";
        string email = GetVendorEmailData(username);
        cout << "Email: " << email << ";\tResult: ";
        redisReply *reply = (redisReply*)redisCommand(redis, "XADD vendor * operation_id 1 username %s password %s email %s", username.c_str(), email.c_str(), password.c_str());
        string rid = reply->str;
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("1")){
            cout << "SUCCESS" << endl;
            int id = stoi(GetFirstEntryElements(reply)->element[3]->str); 
            vendorIds.push_back(id);
            } 
        else{cout << "FAIL" << endl;}
    }
    return vendorIds;
}

vector<int> VendorCreateInsertions(redisContext *redis, vector<int> vendorIds){
    int size = vendorIds.size();

    vector<int> productIds;
    vector<string> productNames = GetVendorProductNameData(size);

    for(int i = 0; i < size; i++){
        int id = vendorIds.at(i);
        cout << "Test n." << i + 1 << "\t";
        cout << "Vendor id: " << id << "\t";
        cout << "Product name: " << productNames.at(i) << endl;
    }
    return productIds;
}