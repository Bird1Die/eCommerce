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

vector<Insertion> GetOrderList(Context ctx){
}