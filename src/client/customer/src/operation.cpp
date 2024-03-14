#include "main.h"

vector<Insertion> GetProductList(Context ctx, string name){
    vector<Insertion> insertions;
    char comand[400];
    snprintf(comand, sizeof(comand), 
    "SELECT id, product, price, vendor FROM Insertion WHERE product LIKE '%%%s%%'", name.c_str());
    PGresult *result = ctx.GetDB().ExecSQLtuples(comand);
    for(int i = 0; i < PQntuples(result); i++){
        int id = atoi(PQgetvalue(result, i, 0));
        string name = PQgetvalue(result, i, 1);
        float price = atof(PQgetvalue(result, i, 2));
        snprintf(comand, sizeof(comand),
        "SELECT COUNT (*) FROM Orders WHERE product = %d", id);
        PGresult *sales_query = ctx.GetDB().ExecSQLtuples(comand);
        int sales = atoi(PQgetvalue(sales_query, 0, 0));
        insertions.push_back(Insertion(id, name, price, sales));
    }
    return insertions;
}

bool CreateOrder(Context ctx, Insertion ins, int quantity){
    system("clear");
    cout << "Creating order..." << endl;
    redisReply *reply = RedisCommand(ctx.GetRedis(), 
    "XADD customer * operation_id 2 id_product %d quantity %d id_customer %d", ins.GetId(), quantity, ctx.GetId());
    string rid = reply->str;
    while(true){
        reply = RedisCommand(ctx.GetRedis(), "XREAD COUNT 1 BLOCK 5000 STREAMS %s $", rid.c_str());
        if(reply->elements == 0){continue;}
        redisReply *elements = (redisReply*) GetFirstEntryElements(reply);
        string result = elements->element[1]->str;
        
        if(!result.compare("3")){return true;}
        else{return false;}
    }

}

vector<Insertion> GetOrderList(Context ctx){
    vector<Insertion> s;
    return s;
}