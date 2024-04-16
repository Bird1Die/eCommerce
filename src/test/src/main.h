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

vector<int> VendorRegistation(redisContext *redis);
vector<int> VendorCreateInsertions(redisContext *redis, vector<int>);

// Data retrieve

vector<string> GetVendorUsernameData(int NTEST);
vector<string> GetVendorPasswordData(int NTEST);
string GetVendorEmailData(string name);
vector<string> GetVendorProductNameData(int NTEST);

 