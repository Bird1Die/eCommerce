#include "main.h"

Con2DB CreateDB(){
    // hostname, port, username, password, dbname
    static Con2DB db("localhost", "5432", "ecommerce", "47002", "myecommerce");
    return db;
}

int newRegistrationDB(string username, string email, string password) {
    Con2DB db = CreateDB();

    cout << "Username: " << username << endl << "Email: " << email << endl << "Password: "<< password <<endl;

    char command[200];
    sprintf(command, "BEGIN"); 
    PGresult *result = db.ExecSQLcmd(command);

    snprintf(command, sizeof(command), 
        "SELECT * FROM Vendor WHERE email = '%s';", email.c_str());
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result) > 0) {
        return -1;
    }

    snprintf(command, sizeof(command), 
        "SELECT * FROM Vendor WHERE username = '%s';", username.c_str());
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result) > 0) {
        return -1;
    }
    
    snprintf(command, sizeof(command),
     "INSERT INTO vendor (username, password, email) VALUES ('%s', '%s', '%s') RETURNING id;", 
      username.c_str(), password.c_str(), email.c_str());
    
   
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        return -1;
    }

    int id = atoi(PQgetvalue(result, 0, 0));
    sprintf(command, "COMMIT"); 
    result = db.ExecSQLcmd(command);
    //PQclear(result);
    return id;
}

int newInsertionDB(string product_name, string price, string id_vendor) {
    double real_price;
    int id_int;
    if(isNumerical(price) && isIntNumerical(id_vendor)){
        //price = atof(price.c_str());
        double d_price = stod(price);
        real_price = floor(d_price*100)/100;
        id_int = stoi(id_vendor);
    } else {
        return -1;
    }
    
    char command[200];
    Con2DB db = CreateDB();

    snprintf(command, sizeof(command), 
     "INSERT INTO Insertion (product, price, vendor) VALUES ('%s', '%f', '%d');",
     product_name.c_str(), real_price, id_int);
    
    PGresult *result = db.ExecSQLcmd(command);
    if (!(PQresultStatus(result) == PGRES_COMMAND_OK)) {
        return -1;
    } 
    return 0;
}

int loginDB(string email, string password) {
    char command[200];
    Con2DB db = CreateDB();
    snprintf(command, sizeof(command), 
        "SELECT id FROM Vendor WHERE email = '%s' AND password = '%s';", 
        email.c_str(), password.c_str());
    PGresult *result = db.ExecSQLtuples(command);
    if (!(PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result)) > 0 ) {
        return -1;
    }
    int id = atoi(PQgetvalue(result, 0, 0));
    return id;
}