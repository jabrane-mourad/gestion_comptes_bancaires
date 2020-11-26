#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include "createaccountwidget.h"
#include "accountclientswidget.h"
#include "sortwidget.h"
#include "deletewidget.h"
#include "dbmanager.h"
#include "transactionwidget.h"
#include "searchwidget.h"
#include <QGridLayout>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DbManager *m_db;

private slots:
    void aboutDialogSlot();     // A propos
    void deleteAccountSlot();   // Supprimer Un Compte
    void findAccountSlot();     // Rechercher Un Compte
    void updateAccountSlot();   // Modifier Un Compte
    void createAccountSlot();   // Creer Un Compte
    void sortAccountSlot();     // Trier Un Compte
    void transactionsSlot();    // Transactions

private:
    Ui::MainWindow *ui;
    CreateAccountWidget *createwidget;
    AccountClientsWidget *updatewidget;
    SortWidget *sortwidget;
    DeleteWidget *deletewidget;
    TransactionWidget *transactionswidget;
    SearchWidget *searchwidget;
    QGridLayout *m_layout;
};

#endif // MAINWINDOW_H
