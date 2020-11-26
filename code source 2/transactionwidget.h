#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QSqlQueryModel>
#include "dbmanager.h"

namespace Ui {
class TransactionWidget;
}

class TransactionWidget : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionWidget(DbManager *db, QWidget *parent = nullptr);
    ~TransactionWidget();

private slots:
    void on_cancelButton_clicked();

    void on_cancelButton2_clicked();

    void on_cancelButton3_clicked();

    void on_tabWidget_tabBarClicked(int index);     // resize window when tab is changed

    void on_depositButton_clicked();        // When 'Deposer' is clicked

    void on_depositButton_2_clicked();      // When 'Tirer' is clicked

    void on_exchangeButton_clicked();

    void on_cancelButton_2_clicked();

    void on_downloadButton_clicked();

private:
    void closeEvent(QCloseEvent *bar);
    Ui::TransactionWidget *ui;
    DbManager *m_db;
    QSqlQueryModel *m_model;
};

#endif // TRANSACTIONWIDGET_H
