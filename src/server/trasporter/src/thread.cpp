#include "main.h"

void manageThread(string operation, redisReply *reply, redisContext *redis) {
    switch (stoi(operation))
            {
            case 1: 
                cout << "Registrazione" << endl;
                newRegistrationMsg(reply, redis);
                break;
            case 2:
                cout << "Change shipping status" << endl;
                changeShippingStatusMsg(reply, redis);
                break;
            case 3: 
                cout << "Login" << endl;   
                loginMsg(reply, redis); 
                break;
            case 4:
                cout << "Request new Shipping" << endl;
                requestShippingMsg(reply, redis);
            }
}

void inputListener(bool &run) {
    int ch;
    while (run) {
        ch = getch();
        if (ch == 27) { // Tasto ESC
            run = false;
        }
    }
}

int redisListener(redisContext *redis, bool &run) {
    redisReply *reply;
    vector <thread> threads;
    while (run) {
        reply = (redisReply *)redisCommand(redis, "XREAD COUNT 1 BLOCK 10000 STREAMS transporter $");
        if (reply && reply->elements != 0) {
            redisReply *prima_reply = reply->element[0];
            cout << "Stream name: " << prima_reply->element[0]->str << endl;
            redisReply *single_entry = prima_reply->element[1]->element[0];
            string entry_number = single_entry->element[0]->str;
            string operation = single_entry->element[1]->element[1]->str;
            cout << "Entry: " << entry_number << ", operationID: " << operation << endl; 
            thread th(manageThread, operation, reply, redis);
            threads.push_back(move(th));
            freeReplyObject(reply);
        }
    }
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}