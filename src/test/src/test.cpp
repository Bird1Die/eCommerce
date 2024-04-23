#include "main.h"

vector<int> VendorRegistation(redisContext *redis){
    vector<int> vendorIds;
    vector<string> vendorUsernames = GetVendorUsernameData(NTEST);
    vector<string> vendorPasswords = GetPasswordData(NTEST);
    for(int i = 0; i < NTEST; i++){
        cout << "Test n." << i + 1 << "\t";
        string username = vendorUsernames.at(i);
        cout << "Username: " << username << ";\t";
        string password = vendorPasswords.at(i);
        cout << "Password: " << password << ";\t";
        string email = GetVendorEmailData(username);
        cout << "Email: " << email << ";\tResult: ";

        // Redis command test
        redisReply *reply = (redisReply*)redisCommand(redis, "XADD vendor * operation_id 1 username %s password %s email %s", username.c_str(), email.c_str(), password.c_str());
        string rid = reply->str;

        // Getting result
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

void VendorCreateInsertion(redisContext *redis, vector<int> vendorIds){
    int size = vendorIds.size();

    vector<string> productNames = GetVendorProductNameData(size);

    for(int i = 0; i < size; i++){
        cout << "Test n." << i + 1 << ";\t";
        int id = vendorIds.at(i);
        cout << "Vendor id: " << id << ";\t";
        string name = productNames.at(i);
        cout << "Product name: " << name << ";\t";
        float price = GetRandomPrice();
        cout << "Price: " << price << ";\tResult: ";

        // Redis command test
        redisReply *reply = (redisReply*) redisCommand(redis, "XADD vendor * operation_id 2 product_name %s price %.2f id_vendor %d", name.c_str(), price, id);
        string rid = reply->str;

        // Getting result
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("3")){cout << "SUCCESS" << endl;} 
        else{cout << "FAIL" << endl;}

    }
    return;
}

vector<int> CustomerRegistation(redisContext *redis){
    vector<int> customerIds;
    vector<string> CustomerUsernames = GetCustomerUsernameData(NTEST);
    vector<string> CustomerPasswords = GetPasswordData(NTEST);
    for(int i = 0; i < NTEST; i++){
        cout << "Test n." << i + 1 << "\t";
        string username = CustomerUsernames.at(i);
        cout << "Username: " << username << ";\t";
        string password = CustomerPasswords.at(i);
        cout << "Password: " << password << ";\t";
        string email = GetVendorEmailData(username);
        cout << "Email: " << email << ";\tResult: ";
        redisReply *reply = (redisReply*)redisCommand(redis, "XADD customer * operation_id 1 username %s password %s email %s", username.c_str(), email.c_str(), password.c_str());
        string rid = reply->str;
        reply = (redisReply*) redisCommand(redis,  "XREAD COUNT 1 BLOCK 2000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){cout << "FAIL: NO RESPONSE" << endl; continue;}
        string result = GetFirstEntryElements(reply)->element[1]->str;
        
        if(!result.compare("1")){
            cout << "SUCCESS" << endl;
            int id = stoi(GetFirstEntryElements(reply)->element[3]->str); 
            customerIds.push_back(id);
            } 
        else{cout << "USER ALREADY EXISTS" << endl;}
    }
    return customerIds;
}

void CustomerCreateOrder(redisContext *redis, vector<int> customerIds){
    
}