#include "dbmanager.h"

DbManager::DbManager()
{

    // Initialize & open Database
    m_db = new QSqlDatabase();
    *m_db = QSqlDatabase::addDatabase(QString("QSQLITE"));
    m_db->setDatabaseName(QString("C:\\Users\\daruom\\Desktop\\Bank20190522\\Bank20190522\\DB\\Bank20190617.sqlite"));

    m_db->close(); // close if already open
    m_db->open();

    if ( m_db->isOpen() )
        qDebug() << "Database is Connected";
    else
        qDebug() << "Database is NOT Connected: " << m_db->lastError();
}

bool DbManager::doesClientExists(int id){
    /*
     * Return True if client exists in the Database
     * Otherwise return false, or output a debug warning
     * id : The field 'id_client' in the Database.
    */

    QString accountID = QString(id);

    m_db->open();
    QSqlQuery query(*m_db);
    query.prepare("SELECT * FROM clients WHERE id_client=:id");
    query.bindValue(":id", id);

    if ( query.exec() ) {
        return query.next()? true: false;
    } else
        qDebug() << "Query NOT Executed" <<  query.lastError();return false;
}

bool DbManager::addClient(QString nom, QString prenom, int age, QString adresse, int tel) {
    /*
     * Add Client to Database & Return True if Operation is successfull
     * Otherwise Return False.
     */

    QSqlQuery query(*m_db);
    query.prepare("INSERT INTO clients (nom, prenom, age, adresse, tel)"
                  " VALUES (:nom, :prenom, :age, :adresse, :tel) ");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", age);
    query.bindValue(":adresse", adresse);
    query.bindValue(":tel", tel);

    return query.exec() ? true : false;
}

bool DbManager::addAccount(double solde, QString type, int id_client) {
    /*
     * Add Account to Database & Return True if operation is successfull,
     * Otherwise return false.
     */


    QSqlQuery query(*m_db);
    query.prepare("INSERT INTO comptes (date_creation, solde, type, id_client) "
                  "VALUES (CURRENT_TIMESTAMP, :solde, :type, :id_client)");
    query.bindValue(":solde", solde);
    query.bindValue(":type", type);
    query.bindValue(":id_client", id_client);

    return query.exec()? true: false;
}

int DbManager::getClientID(QString nom, QString prenom, int age, QString adresse, int tel){
    /*
     * Return the Account ID from database base on: nom, prenom, age, adresse, tel.
     * By default we suppose there is NO REDUNDANT clients in the Database
     * Return -1 if Client doesnt exists in the Database
     * Return -2 if query is NOT executed
    */

    QSqlQuery query(*m_db);
    query.prepare("SELECT id_client FROM clients WHERE "
                  "nom=:nom AND prenom=:prenom AND age=:age AND adresse=:adresse AND tel=:tel");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", age);
    query.bindValue(":adresse", adresse);
    query.bindValue(":tel", tel);

    bool queryresult = query.exec();
    if ( queryresult )
        return query.next()? query.value(0).toInt() : -1;
    else
        return -2;

}

bool DbManager::isClientRedoundant(QString nom, QString prenom, int age, QString adresse, int tel){
    /*
     * Return True if client is redundant in the database,
     * otherwiser return false.
     */

    QSqlQuery query(*m_db);
    query.prepare("SELECT id_client FROM clients WHERE "
                  "nom=:nom AND prenom=:prenom AND age=:age AND adresse=:adresse AND tel=:tel");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", age);
    query.bindValue(":adresse", adresse);
    query.bindValue(":tel", tel);

    query.exec();
    return (query.next())? true : false;
}

bool DbManager::doesAccountExists(int account_id){
    /*
     * Return True if account exists in the database,
     * otherwise return false
     */

    QSqlQuery query(*m_db);
    query.prepare("SELECT id_compte FROM comptes WHERE id_compte=:account_id");
    query.bindValue(":account_id", account_id);

    query.exec();
    return query.next()? true : false;
}

QSqlQuery DbManager::query_nom(QString nom){
    /* Execute and return query with the condition of NOM */

    QSqlQuery query(*m_db);
    query.prepare("select id_compte, nom, prenom, solde, date_creation, tel from comptes join clients on comptes.id_client = clients.id_client where clients.nom=:nom;");
    query.bindValue(":nom", nom);

    query.exec();
    return query;
}

QSqlQuery DbManager::query_prenom(QString prenom){
    /* Execute and return query with the condition of PRENOM */

    QSqlQuery query(*m_db);
    query.prepare("select id_compte, nom, prenom, solde, date_creation, tel from comptes join clients on comptes.id_client = clients.id_client where clients.prenom=:prenom;");
    query.bindValue(":prenom", prenom);

    query.exec();
    return query;
}

QSqlQuery DbManager::query_accountid(QString accountid){
    /* Execute and return query with the condition of id_compte */

    QSqlQuery query(*m_db);
    query.prepare("SELECT id_compte, nom, prenom, solde, date_creation, tel "
                  "FROM comptes JOIN clients ON "
                  "comptes.id_client = clients.id_client WHERE id_compte=:id_compte");
    query.bindValue(":id_compte", accountid.toInt());

    query.exec();
    return query;
}

QSqlDatabase DbManager::getDB() const {
    return *m_db;
}

QSqlQuery DbManager::sortByAccountId(){

    QSqlQuery query(*m_db);
    query.prepare("SELECT comptes.id_compte AS 'Numero De Compte', comptes.solde,"
                  " clients.nom, clients.prenom, comptes.date_creation, comptes.type, clients.adresse, clients.tel, clients.age"
                  " FROM comptes JOIN clients ON comptes.id_client=clients.id_client ORDER BY comptes.id_compte");

    query.exec();
    return query;
}

QSqlQuery DbManager::sortByDate(){
    QSqlQuery query(*m_db);
    query.prepare("SELECT comptes.id_compte AS 'Numero De Compte', comptes.solde,"
                  " clients.nom, clients.prenom, comptes.date_creation, comptes.type, clients.adresse, clients.tel, clients.age"
                  " FROM comptes JOIN clients ON comptes.id_client=clients.id_client ORDER BY comptes.date_creation");

    query.exec();
    return query;
}

QSqlQuery DbManager::sortByCredit(){
    QSqlQuery query(*m_db);
    query.prepare("SELECT comptes.id_compte AS 'Numero De Compte', comptes.solde,"
                  " clients.nom, clients.prenom, comptes.date_creation, comptes.type, clients.adresse, clients.tel, clients.age"
                  " FROM comptes JOIN clients ON comptes.id_client=clients.id_client ORDER BY comptes.solde");

    query.exec();
    return query;
}

QSqlQuery DbManager::sortByNom(){
    QSqlQuery query(*m_db);
    query.prepare("SELECT comptes.id_compte AS 'Numero De Compte', comptes.solde,"
                  " clients.nom, clients.prenom, comptes.date_creation, comptes.type, clients.adresse, clients.tel, clients.age"
                  " FROM comptes JOIN clients ON comptes.id_client=clients.id_client ORDER BY clients.nom");

    query.exec();
    return query;
}

QSqlQuery DbManager::sortByPrenom(){
    QSqlQuery query(*m_db);
    query.prepare("SELECT comptes.id_compte AS 'Numero De Compte', comptes.solde,"
                  " clients.nom, clients.prenom, comptes.date_creation, comptes.type, clients.adresse, clients.tel, clients.age"
                  " FROM comptes JOIN clients ON comptes.id_client=clients.id_client ORDER BY clients.prenom");

    query.exec();
    return query;
}

bool DbManager::deleteAccount(int AccountId){
    /* if client associated with this account has only account, delete client and account record.
     * otherwise delete only account record and leave the client */

    QSqlQuery query(*m_db);

    int id_account = AccountId, id_client = getClientID(id_account);

    query.prepare("DELETE FROM comptes WHERE id_compte=:id_account");
    query.bindValue(":id_account", id_account);

    bool delAccount =  query.exec();        // delete account
    bool delClient = false;

    if ( hasMultipleAccounts(id_client, false) ){
        query.prepare("DELETE FROM clients WHERE id_client=:id_client");
        query.bindValue(":id_client", id_client);
        delClient =  query.exec();
    }

    return (delClient && delAccount ) ? true : false;
}

bool DbManager::deposit(int accountid, double amount){
    QSqlQuery query(*m_db);
    query.prepare("UPDATE comptes SET solde=solde+:amount WHERE id_compte=:accountid");
    query.bindValue(":amount", amount);
    query.bindValue(":accountid", accountid);
    bool queryresut = query.exec();

    if ( queryresut ){
        // update transactions account
        QSqlQuery query2(*m_db);
        query2.prepare("INSERT INTO transactions (date_transaction, type_transaction, montant, id_source)"
                       " VALUES (CURRENT_TIMESTAMP, :type, :amount, :source)");
        query2.bindValue(":type", QString("Deposition"));
        query2.bindValue(":amount", amount);
        query2.bindValue(":source", accountid);
        query2.exec();
        return true;
    } else
        return false;
}

QString DbManager::getAccountName(int accountid) const{
    QSqlQuery query(*m_db);
    query.prepare("SELECT clients.nom || ' ' || clients.prenom FROM clients JOIN comptes"
                  " on clients.id_client = comptes.id_client WHERE comptes.id_compte=:accountid");
    query.bindValue(":accountid", accountid);
    qDebug() << query.exec();
    query.next(); // put cursor on the first record
    return query.value(0).toString();
}

QString DbManager::getAccountAmount(int accountid) const{
    QSqlQuery query(*m_db);
    query.prepare("SELECT solde FROM comptes WHERE id_compte=:accountid");
    query.bindValue(":accountid", accountid);
    qDebug() << query.exec();
    query.next();
    return query.value(0).toString();
}

int DbManager::draw(int accountid, double amount){
    /*
     * draw 'amoun't from account identified by 'accountid'
     * return 1 if operation is successfull
     * return 0 if operation is unsuccessfull ( due to query execution )
     * return -1 if the account has no money to draw
     */

    QSqlQuery query(*m_db);
    double availableamount = 0.0;

    // check if there is available amount on the account first
    query.prepare("SELECT solde FROM comptes WHERE id_compte=:accountid");
    query.bindValue(":accountid", accountid);
    query.exec();query.next();
    availableamount = query.value(0).toDouble();

    qDebug() << "Draw Method\n";
    qDebug() << "Available Amount" <<  availableamount;
    qDebug() << "Amount: " << amount;

    // draw money from account
    if ( availableamount < amount )
        return -1;
    else {
        query.prepare("UPDATE comptes SET solde=solde-:amount WHERE id_compte=:accountid");
        query.bindValue(":amount", amount);
        query.bindValue(":accountid", accountid);
        bool queryresult = query.exec();

        if ( queryresult ){
            // update transactions account
            QSqlQuery query2(*m_db);
            query2.prepare("INSERT INTO transactions (date_transaction, type_transaction, montant, id_source)"
                           " VALUES (CURRENT_TIMESTAMP, :type, :amount, :source)");
            query2.bindValue(":type", QString("Tirage"));
            query2.bindValue(":amount", amount);
            query2.bindValue(":source", accountid);
            query2.exec();
            return true;
        } else
            return false;
    }
}

int DbManager::transfer(int source, int destination, double amount){
    /*
     * transfert money from source account to destination account
     * return 0 if no error occured
     * return -1 if source doesnt have the available money to transfer
     * return 1 if  an error occured
     */
    QSqlQuery query(*m_db);
    double availableamount = 0.0;

    /* get available money from source */
    query.prepare("SELECT solde FROM comptes WHERE id_compte=:source");
    query.bindValue(":source", source);
    query.exec();query.next();
    availableamount = query.value(0).toDouble();

    if ( availableamount < amount )
        return -1;
    else {
        /* draw money from source */
        query.prepare("UPDATE comptes SET solde=solde-:amount WHERE id_compte=:source");
        query.bindValue(":amount", amount);
        query.bindValue(":source", source);
        qDebug() << query.exec();

        /* deposit money to destination */
        query.prepare("UPDATE comptes SET solde=solde+:amount WHERE id_compte=:destination");
        query.bindValue(":amount", amount);
        query.bindValue(":destination", destination);
        qDebug() << query.exec();

        /* add transactions to database */
        query.prepare("INSERT INTO transactions (date_transaction, type_transaction, montant, id_source, id_destination)"
                      " VALUES (CURRENT_TIMESTAMP, :type, :amount, :source, :destination)");
        query.bindValue(":type", QString("Transfert"));
        query.bindValue(":amount", amount);
        query.bindValue(":source", source);
        query.bindValue(":destination", destination);
        qDebug() << query.exec();

        return 0;
    }

}

QSqlQuery DbManager::transactionsLog(int type, int sortby){
    /*
     * return query base on 'type' and 'sortby'
     * type:
     *      0: everything *
     *      1: deposition
     *      2: tirage
     *      3: transfert
     * sortby:
     *      0: date
     *      1: source
     *      2: destination
     *      3: montant
     *
     * Examples:
     * type = 0, sortby = 0:  query * sorted by date.
     * type = 1, sortby = 0;  query * sorted by source account id
     * type = 2, sortby = 1; query trirage sorted by source account id
     */

    QSqlQuery query(*m_db);

    // define some query

    // Query every type
    QString query1 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions ORDER BY 2";
    QString query2 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions ORDER BY 4";
    QString query3 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions ORDER BY 5";
    QString query11 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                      "id_destination AS 'Destination' FROM transactions ORDER BY 3";

    // Query 'Depostion'
    QString query4 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Deposition' ORDER BY 2";
    QString query5 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Deposition' ORDER BY 4";
    QString query12 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Deposition' ORDER BY 3";

    // Query 'Tirage'
    QString query6 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Tirage' ORDER BY 2";
    QString query7 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Tirage' ORDER BY 4";
    QString query13 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Tirage' ORDER BY 3";

    // Query 'Transfert'
    QString query8 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Transfert' ORDER BY 2";
    QString query9 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                     "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Transfert' ORDER BY 4";
    QString query10 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                      "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Transfert' ORDER BY 5";
    QString query14 = "SELECT type_transaction AS 'Type', date_transaction AS 'Date', montant AS 'Montant', id_source AS 'Source',"
                      "id_destination AS 'Destination' FROM transactions WHERE type_transaction='Transfert' ORDER BY 3";



    if ( type == 0 ){
        if ( sortby == 0 )
            query.prepare(query1);
        if ( sortby == 1 )
            query.prepare(query2);
        if ( sortby == 2 )
            query.prepare(query3);
        if ( sortby == 3 )
            query.prepare(query11);
    }
    if( type == 1 ) {
        if ( sortby == 0 )
            query.prepare(query4);
        if ( sortby == 1 )
            query.prepare(query5);
        if ( sortby == 2 )
            query.prepare(query5);
        if ( sortby == 3 )
            query.prepare(query12);
    }
    if ( type == 2 ){
        if ( sortby == 0 )
            query.prepare(query6);
        if ( sortby == 1 )
            query.prepare(query7);
        if ( sortby == 2 )
            query.prepare(query7);
        if ( sortby == 3 )
            query.prepare(query13);
    }
    if ( type == 3 ){
        if ( sortby == 0 )
            query.prepare(query8);
        if ( sortby == 1 )
            query.prepare(query9);
        if ( sortby == 2 )
            query.prepare(query10);
        if ( sortby == 3 )
            query.prepare(query14);
    }
    qDebug() << query.exec();
    return query;
}

QSqlQuery DbManager::searchByAccountID(int accountid){

    /* Search database by Account ID and return query */
    QSqlQuery query(*m_db);
    query.prepare("SELECT comptes.id_compte AS 'Numero De Compte', clients.id_client AS 'ID Client', comptes.date_creation AS 'Date de Creation',"
                  "solde, type AS 'Type de Comtpe', clients.nom AS 'Nom', clients.prenom AS 'Prenom',"
                  "clients.age AS 'Age', adresse AS 'Adresse', tel as 'Telephone' FROM clients JOIN comptes ON"
                  " clients.id_client=comptes.id_client WHERE comptes.id_compte=:accountid");
    query.bindValue(":accountid", accountid);
    qDebug() << query.exec();
    return query;
}

QSqlQuery DbManager::searchByNom(QString nom){
    /* Search database by 'Nom' and return query */

    QSqlQuery query(*m_db);
    query.prepare("SELECT comptes.id_compte AS 'Numero De Compte', clients.id_client AS 'ID Client', comptes.date_creation AS 'Date de Creation',"
                  "solde, type AS 'Type de Comtpe', clients.nom AS 'Nom', clients.prenom AS 'Prenom',"
                  "clients.age AS 'Age', adresse AS 'Adresse', tel as 'Telephone' FROM clients JOIN comptes ON"
                  " clients.id_client=comptes.id_client WHERE clients.nom=:nom");
    query.bindValue(":nom", nom);
    qDebug() << query.exec();
    return query;
}

QSqlQuery DbManager::searchByPrenom(QString prenom){
    /* Search database by 'Prenom' and return query */

    QSqlQuery query(*m_db);
    query.prepare("SELECT comptes.id_compte AS 'Numero De Compte', clients.id_client AS 'ID Client', comptes.date_creation AS 'Date de Creation',"
                  "solde, type AS 'Type de Comtpe', clients.nom AS 'Nom', clients.prenom AS 'Prenom',"
                  "clients.age AS 'Age', adresse AS 'Adresse', tel as 'Telephone' FROM clients JOIN comptes ON"
                  " clients.id_client=comptes.id_client WHERE clients.prenom=:prenom");
    query.bindValue(":prenom", prenom);
    qDebug() << query.exec();
    return query;
}

QSqlQuery DbManager::searchClientsWithMultipleAccounts(int n){
    /* query the clients having more than n accounts */

    QSqlQuery query(*m_db);
    query.prepare("SELECT COUNT(*) AS 'Nombre De Compte', clients.nom AS 'NOM', clients.prenom AS 'PRENOM', SUM(comptes.solde) AS 'Solde Total', "
                  "clients.age AS 'Age', clients.adresse AS 'Adresse', clients.tel AS 'Telephone' "
                  "FROM clients JOIN comptes ON clients.id_client=comptes.id_client GROUP BY clients.id_client "
                  "HAVING count(comptes.id_client) >= :n;");
    query.bindValue(":n", n);

    qDebug() << query.exec();
    return query;
}

QSqlQuery DbManager::searchClientsWithAgeRange(int x, int y){
    /* Query clients who's age is in the range [x, y] */

    QSqlQuery query(*m_db);
    query.prepare("SELECT clients.nom AS 'NOM', clients.prenom AS 'PRENOM', SUM(comptes.solde) AS 'Solde Total', "
                  "clients.age AS 'Age', clients.adresse AS 'Adresse', clients.tel AS 'Telephone' "
                  "FROM clients JOIN comptes ON clients.id_client=comptes.id_client GROUP BY clients.id_client "
                  "HAVING clients.age BETWEEN :x AND :y");
    query.bindValue(":x", x);
    query.bindValue(":y", y);

    qDebug() << query.exec();
    return query;
}

QSqlQuery DbManager::searchClientsWithAmountComparison(double amount, int op){
    /*
     * if op = 1, query clients having total amount SUPERIOR to amount
     * if op = 0, query clients having total amount INFERIOR to amount
     */

    QSqlQuery query1(*m_db), query2(*m_db);
    query1.prepare("SELECT clients.nom AS 'NOM', clients.prenom AS 'PRENOM', SUM(comptes.solde) AS 'Solde Total', "
                  "clients.age AS 'Age', clients.adresse AS 'Adresse', clients.tel AS 'Telephone' "
                  "FROM clients JOIN comptes ON clients.id_client=comptes.id_client GROUP BY clients.id_client "
                  "HAVING SUM(comptes.solde) > :amount");
    query2.prepare("SELECT clients.nom AS 'NOM', clients.prenom AS 'PRENOM', SUM(comptes.solde) AS 'Solde Total', "
                  "clients.age AS 'Age', clients.adresse AS 'Adresse', clients.tel AS 'Telephone' "
                  "FROM clients JOIN comptes ON clients.id_client=comptes.id_client GROUP BY clients.id_client "
                  "HAVING SUM(comptes.solde) < :amount");
    query1.bindValue(":amount", amount); query2.bindValue(":amount", amount);
    if ( op ){
        qDebug() << query1.exec();
        return query1;
    } else {
        qDebug() << query2.exec();
        return query2;
    }
}

QString DbManager::getTotalAmount() const{
    /* Return the sum of all amounts on database */
    QSqlQuery query(*m_db);
    query.prepare("SELECT ROUND(SUM(solde), 2) FROM comptes");
    qDebug() << query.exec();
    query.next();
    return query.value(0).toString();
}

QString DbManager::getTotalAccounts() const {
    /* Return the number of total accounts */
    QSqlQuery query(*m_db);
    query.prepare("SELECT COUNT(*) FROM comptes");
    qDebug() << query.exec();
    query.next();
    return  query.value(0).toString();
}

QString DbManager::getTotalClients() const {
    /* Return the number of total clients */
    QSqlQuery query(*m_db);
    query.prepare("SELECT COUNT(*) FROM clients");
    qDebug() << query.exec();
    query.next();
    return query.value(0).toString();
}

QString DbManager::getAverageAges() const {
    /* return the average of ages */
    QSqlQuery query(*m_db);
    query.prepare("SELECT ROUND(AVG(age), 2) FROM clients");
    qDebug() << query.exec();
    query.next();
    return query.value(0).toString();
}
QString DbManager::getAverageAmount() const {
    /* return the average of amounts */
    QSqlQuery query(*m_db);
    query.prepare("SELECT ROUND(AVG(solde), 2) FROM comptes");
    qDebug() << query.exec();
    query.next();
    return query.value(0).toString();
}

QSqlQuery DbManager::getAccount(int accountid ) {
    /* query an account based on the accound it */
    /* this function suppose the account already exists */

    QSqlQuery query(*m_db);
    query.prepare("SELECT * FROM comptes JOIN clients ON comptes.id_client=clients.id_client"
                  " WHERE comptes.id_compte=:accountid");
    query.bindValue(":accountid", accountid);
    qDebug() << query.exec();
    query.next();
    return query;
}

bool DbManager::updateClient(int client_id, QString nom, QString prenom, int age, QString adresse, QString tel){

    QSqlQuery query(*m_db);
    query.prepare("UPDATE clients SET nom=:nom, prenom=:prenom,"
                  " age=:age, adresse=:adresse, tel=:tel WHERE id_client=:id_client");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":age", age);
    query.bindValue(":adresse", adresse);
    query.bindValue(":tel", tel);
    query.bindValue(":id_client", client_id);

    bool queryResult = query.exec();
    qDebug() << queryResult;
    return queryResult ? true : false;
}

bool DbManager::updateAccountType(int account_id, QString account_type){

    QSqlQuery query(*m_db);
    query.prepare("UPDATE comptes SET type=:type WHERE id_compte=:accountID");
    query.bindValue(":accountID", account_id);
    query.bindValue(":type", account_type);

    bool queryResult = query.exec();
    qDebug() << queryResult;

    return queryResult ? true : false;
}

bool DbManager::hasMultipleAccounts(int id, bool search_by_account){
    /* Return True if client has multiple accounts
     * if 'search_by_account' is true, 'id' become id_account.
     * if 'search_by_accout' is false, 'id' becomes id_client.
     */

    int id_client = (search_by_account)? getClientID(id) : id;
    QSqlQuery query(*m_db);
    query.prepare("SELECT id_compte FROM comptes WHERE id_client=:id_client");
    query.bindValue(":id_client", id_client);
    qDebug() << "query from hasMultipleAccounts() : " << query.exec();
    return (query.next() && query.next() )? true: false;
}

int DbManager::getClientID(int id_account){
    /* searth the table 'comptes' and return id_client associated with id_account */

    QSqlQuery query(*m_db);
    query.prepare("SELECT id_client FROM comptes WHERE id_compte=:id_account");
    query.bindValue(":id_account", id_account);
    qDebug() << "Query from getClientID() : " << query.exec();
    query.next();

    return query.value(0).toString().toInt();
}
