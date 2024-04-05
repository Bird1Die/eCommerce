#include "main.h"

/*
redis server listening requests from redis vendor client.
*/
int main(){
    /*
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    */
    redisContext *redis = redisConnect("localhost", 6379);
    system("clear");
    bool run = true;
    while(run) {
        /*
        int ch = getch(); // Ottieni il carattere premuto
        if (ch == 27) { // Verifica se è stato premuto il tasto ESC
            run = false;
            break;
        }
        */
        redisReply *reply = (redisReply*) redisCommand(redis, "XRANGE transporter - + COUNT 1");
        if (reply->elements != 0){
        redisReply *prima_reply = reply->element[0];
        string id = prima_reply->element[0]->str;
        cout << id << endl;
        string operation = prima_reply->element[1]->element[1]->str;
        cout << "Entry: " << id << ", operationID: " << operation << endl; 
        cout << "3" << endl;
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
        redisCommand(redis, "XDEL transporter %s", id.c_str());
        }
    } 

    // endwin();
    return 0;
}