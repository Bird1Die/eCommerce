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
        system("clear");
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
        string id_entry = prima_reply->element[0]->str;
        string operation = prima_reply->element[1]->element[1]->str;  
        switch (stoi(operation))
            {
            case 1: 
                cout << "Registrazione" << endl;
                newRegistrationMsg(prima_reply->element[0]->str, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, prima_reply->element[1]->element[7]->str, redis);
                break;
            case 2:
                cout << "Change shipping status" << endl;
                changeShippingStatusMsg(prima_reply->element[0]->str, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, redis);
                break;
            case 3: 
                cout << "Login" << endl;   
                loginMsg(prima_reply->element[0]->str, prima_reply->element[1]->element[3]->str, prima_reply->element[1]->element[5]->str, redis); 
                break;
            case 4:
                cout << "Request new Shipping" << endl;
                requestShippingMsg(prima_reply->element[0]->str, prima_reply->element[1]->element[3]->str, redis);
            }
        redisCommand(redis, "XDEL transporter %s", id_entry.c_str());
        }
    } 

    // endwin();
    return 0;
}