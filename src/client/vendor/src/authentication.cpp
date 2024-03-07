#include "main.h"

int Registration(Context ctx){
    system("clear");

    cout << "Email: ";
    string email;
    getline(cin, email);

    cout << "Username: ";
    string username;
    getline(cin, username);

    cout << "Password: ";
    string password;
    getline(cin, password);

    redisReply *reply = (redisReply*) RedisCommand(ctx.GetRedis(), 
    "XADD transporter * operation_id 1 username %s email %s password %s", username, email, password);
    string rid = reply->str;


    return 0;
}
int Login(Context ctx){
    return 0;
}