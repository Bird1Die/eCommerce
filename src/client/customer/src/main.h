#include <hiredis/hiredis.h>
#include <vector>
#include <iostream>
using namespace std;

int main();


// KWD MAN

class Kwd_Man{
private:
    vector<string> keywords;
public:
    Kwd_Man(vector<string>);
    string ToString();
};