#include "main.h"

void Notification(string message){
    system("clear");
    cout << message << flush;
    sleep(1);
}

redisReply* GetFirstEntry(redisReply *reply){return reply->element[0]->element[1]->element[0];}
redisReply* GetFirstEntryElements(redisReply *reply){return reply->element[0]->element[1]->element[0]->element[1];}

Context::Context(Con2DB db, redisContext *redis){
    this->db = db;
    this->redis = redis;}
bool Context::GetDebug(){return this->debug;}
void Context::SetDebug(bool debug){this->debug = debug;}
redisContext* Context::GetRedis(){return this->redis;}
int Context::GetId(){return this->id;}
Con2DB Context::GetDB(){return this->db;}
void Context::SetId(int id){this->id = id;}

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
Shipping::Shipping(int id, string customer_name, string shipping_address, string product_name, int quantity, string status){
        this->id = id;
        this->customer_name = customer_name;
        this->shipping_address = shipping_address;
        this->product_name = product_name;
        this->quantity = quantity;
        this->status = status;
}
int Shipping::GetId(){return this->id;}
string Shipping::GetShippingAddress(){return this->shipping_address;}
string Shipping::GetProductName(){return this->product_name;}
int Shipping::GetQuantity(){return this->quantity;}
string Shipping::GetStatus(){return this->status;}
void Shipping::SetStatus(string status){this->status = status;}