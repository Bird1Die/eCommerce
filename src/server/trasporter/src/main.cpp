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
    vector <thread> threads;
    while(run) {
        /*
        int ch = getch(); // Ottieni il carattere premuto
        if (ch == 27) { // Verifica se è stato premuto il tasto ESC
            run = false;
            break;
        }
        */
        redisReply *reply = (redisReply*) redisCommand(redis, "XREAD COUNT 1 BLOCK 10000 STREAMS transporter $");
        if (reply->elements != 0){
        redisReply *prima_reply = reply->element[0];
        cout << "Stream name: " << prima_reply->element[0]->str << endl;
        redisReply *single_entry = prima_reply->element[1]->element[0];
        string entry_number = single_entry->element[0]->str;
        string operation = single_entry->element[1]->element[1]->str;
        cout << "Entry: " << entry_number << ", operationID: " << operation << endl; 
        thread th(manageThread, operation, reply, redis);
        threads.push_back(move(th));
        }
    } 

    for (auto& th : threads) {
        th.join();
    }
    // endwin();
    return 0;
}