#include <vector>
#include <iostream>
#include "../../../con2redis/src/con2redis.h"
#include <unistd.h>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <csignal>

using namespace std;

const int NTEST = 5;
const int NPRODUCTS = 10;

int main();

// Util

redisReply* GetFirstEntryElements(redisReply *reply);

// Test

void VendorRegistation(redisContext *redis);

// Data retrieve

vector<string> GetCustomerUsernameData(int NTEST);
vector<string> GetCustomerPasswordData(int NTEST);
string GetCustomerEmailData(string name);

 