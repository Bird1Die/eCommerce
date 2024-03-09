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

    bool run = false;
    while(run){
        reply = RedisCommand(ctx.GetRedis(), "XREAD COUNT 1 BLOCK 500 streams %s", rid);
        // Prendere risultato della registrazione
    }
    // Se problema ritorna -2
    // Notification("Failed registration");
    return 0;
}
int Login(Context ctx){
    system("clear");

    cout << "Username: ";
    string username;
    getline(cin, username);

    cout << "Password: ";
    string password;
    getline(cin, password);

    redisReply *reply = (redisReply*) RedisCommand(ctx.GetRedis(),
    "XADD vendor * operation_id 3 username %s password %s", username, password);

    string rid = reply->str;
    bool run = true;

    while(run){
        reply = (redisReply*) RedisCommand(ctx.GetRedis(), "XREAD COUNT 1 BLOCK 500 streams %s", rid);
        // Prendere il risultato del login
    }

    // Se problema ritorna -2
    // Notification("Failed login");
    return 0;
}