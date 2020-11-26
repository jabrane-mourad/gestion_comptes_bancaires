#ifndef ACCOUNTCLIENTSWIDGET_H
#define ACCOUNTCLIENTSWIDGET_H

/*
 * La Fenetre responsable de Modifer les donnees d'un client.
 * Options de Recherche :
 *      - Rechercher par Numero de compte.
 *      - Rechercher par Nom.
 *      - Rechercher par Prenom.
 */

#include <QWidget>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QItemSelection>
#include "dbmanager.h"

namespace Ui {
class AccountClientsWidget;
}

class AccountClientsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AccountClientsWidget(DbManager *db, QWidget *parent = nullptr);
    ~AccountClientsWidget();
private slots:

    // Chane Text Above LineEdit
    void searchByIDSlot(bool checked);
    void searchByNomSlot(bool checked);
    void searchByPrenomSlot(bool checked);

    void searchButtonSlot();                                // When 'Rechercher' is Clicked.
    void searchDBSlot();                                    // Output Data as TableView.
    void cancelButtonSlot();                                // When 'Annuler' is clicked.
    void on_tableView_clicked(const QModelIndex &index);    // When a record on tableView is Clicked
    void on_pushButton_clicked();                           // when 'Sauvegarder' is clicked.

signals:
    void searchSignal();        // Emit this signal when 'Rechercher' is clicked.

private:
    void closeEvent(QCloseEvent *bar);
    Ui::AccountClientsWidget *ui;
    QString nom, prenom, accountid;
    DbManager *m_db;
    QSqlQueryModel *m_model;
    QSqlQuery *m_query;
    QString *m_clientID, *m_accountID;
};

#endif // ACCOUNTCLIENTSWIDGET_H
