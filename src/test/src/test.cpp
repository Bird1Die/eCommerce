#include "main.h"

void VendorRegistation(redisContext *redis){
    vector<string> CustomerUsernames = GetCustomerUsernameData(NTEST);
    vector<string> CustomerPasswords = GetCustomerPasswordData(NTEST);
    for(int i = 0; i < NTEST; i++){
        cout << "Test n." << i + 1 << "\t";
        string username = CustomerUsernames.at(i);
        cout << "Username: " << username << ";\t";
        string password = CustomerPasswords.at(i);
        cout << "Password: " << password << ";\t";
        string email = GetCustomerEmailData(username);
        cout << "Email: " << email << ";\tResult: ";
        redisReply *reply = (redisReply*)redisCommand(redis, "XADD vendor * operation_id 1 username %s password %s email %s", username.c_str(), email.c_str(), password.c_str());
        string rid = reply->str;
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        if(!result.compare("1")){cout << "SUCCESS" << endl;} else{cout << "FAIL" << endl;}
    }
    return;
}

void VendorCreateInsertions(redisContext *redis){
}