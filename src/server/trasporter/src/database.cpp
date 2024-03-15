#include "main.h"

Con2DB CreateDB(){
    // hostname, port, username, password, dbname
    static Con2DB db("localhost", "5432", "ecommerce", "47002", "myecommerce");
    return db;
}

/*
create a new transporter within the database with username, email and password 
received from redis client. It returns the new vendor's id.
*/
int newRegistrationDB(string username, string email, string password) {
    Con2DB db = CreateDB();

    cout << "Username: " << username << endl << "Email: " << email << endl << "Password: "<< password <<endl;

    char command[200];
    sprintf(command, "BEGIN"); 
    PGresult *result = db.ExecSQLcmd(command);

    snprintf(command, sizeof(command), 
        "SELECT * FROM transporter WHERE email = '%s';", email.c_str());
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result) > 0) {
        return -1;
    }

    snprintf(command, sizeof(command), 
        "SELECT * FROM transporter WHERE username = '%s';", username.c_str());
    result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result) > 0) {
        return -1;
    }
    
    snprintf(command, sizeof(command),
     "INSERT INTO transporter (username, password, email) VALUES ('%s', '%s', '%s') RETURNING id;", 
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

/*
create a new shipping within the databse with id_order received
from the redis client.
*/
int newShippingDB(string id_order) {
    Con2DB db = CreateDB();

    int id_transporter = queryShippingToTransporter();
    if (id_transporter < 0) {
        return -1;
    }

    char command[200];
    snprintf(command, sizeof(command), 
    "INSERT INTO shipping (number_order, transporter) VALUES (%d, %d)", id_order, id_transporter);
    PGresult *result = db.ExecSQLcmd(command);
    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        return -1;
    }
    return 0;
}

/*
query to find a transporter with the fewest shipping loaded. It returns the transporter'id.

int queryShippingToTransporter() {
    Con2DB db = CreateDB();
    char command[200];
    snprintf(command, sizeof(command),
    "Select t.id, count (s.id) as ship From transporter t left outer join shipping s on s.transporter = t.id group by t.id Order by ship asc");
    
    PGresult *result = db.ExecSQLtuples(command);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        return -1;
    }

    int id_transporter = atoi(PQgetvalue(result, 0, 0));
    return id_transporter;
}
*/

/*
login by searching within the database an entity with the same username and password as given 
in the redis message. It returns id of the entity.
*/
int loginDB(string username, string password) {
    cout << "Cerco l'utente: " << username << endl;
    char command[200];
    Con2DB db = CreateDB();
    snprintf(command, sizeof(command), 
        "SELECT id FROM transporter WHERE username = '%s' AND password = '%s';", 
        username.c_str(), password.c_str());
    PGresult *result = db.ExecSQLtuples(command);
    if (!((PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result)) > 0 )) {
        return -1;
    }
    int id = atoi(PQgetvalue(result, 0, 0));
    return id;
}

int requestShippingDB(int id_transporter) {
    system("clear");
    cout << "Cerco un ordine pronto per la spedizione..." << endl;
    char command[200];
    Con2DB db = CreateDB();
    snprintf(command, sizeof(command),
    "SELECT o.id FROM orders o WHERE o.assigned='false' ORDER BY o.instant_date ASC");
    PGresult *result = db.ExecSQLtuples(command);
    if (!((PQresultStatus(result) == PGRES_TUPLES_OK && PQntuples(result)) > 0 )) {
        return -1;
    }
    int id_order = atoi(PQgetvalue(result, 0, 0));
    snprintf(command, sizeof(command),
    "INSERT INTO shipping ()")
}