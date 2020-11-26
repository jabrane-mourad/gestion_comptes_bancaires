#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>

class DbManager
{
public:
    DbManager();

    bool doesClientExists(int id);
    bool addClient(QString nom, QString prenom, int age,
                    QString adresse, int tel);
    int getClientID(QString nom, QString prenom, int age,
                    QString adresse, int tel);
    int getClientID(int id_account);
    bool isClientRedoundant(QString nom, QString prenom, int age,
                    QString adresse, int tel);
    bool updateClient(int client_id, QString nom, QString prenom, int age,
                      QString adresse, QString tel);
    bool updateAccountType(int account_id, QString account_type);
    bool doesAccountExists(int account_id);
    bool addAccount(double solde, QString type, int id_client);
    bool deposit(int accountid, double amount);
    int draw(int accountid, double amount);
    int transfer(int source, int destination, double amount);

    bool hasMultipleAccounts(int id_account, bool search_by_account=true);

    // execute some queries and return result
    QSqlQuery query_nom(QString nom);
    QSqlQuery query_prenom(QString prenom);
    QSqlQuery query_accountid(QString accountid);
    bool deleteAccount(int AccountId);
    QSqlQuery transactionsLog(int type, int sortby);

    // searsh queries
    QSqlQuery searchByAccountID(int accountid);
    QSqlQuery searchByNom(QString nom);
    QSqlQuery searchByPrenom(QString prenom);
    QSqlQuery searchClientsWithMultipleAccounts(int n);
    QSqlQuery searchClientsWithAgeRange(int x, int y);
    QSqlQuery searchClientsWithAmountComparison(double amount, int op);

    // sort queries
    QSqlQuery sortByAccountId();
    QSqlQuery sortByDate();
    QSqlQuery sortByCredit();
    QSqlQuery sortByNom();
    QSqlQuery sortByPrenom();

    // getter
    QSqlDatabase getDB() const;
    QString getAccountName(int accountid) const;
    QString getAccountAmount(int accountid) const;
    QString getTotalAmount() const;
    QString getTotalAccounts() const;
    QString getTotalClients() const;
    QString getAverageAmount() const;
    QString getAverageAges() const;
    QSqlQuery getAccount(int accountid);

private:
    QSqlDatabase *m_db;
};


#endif // DBMANAGER_H
