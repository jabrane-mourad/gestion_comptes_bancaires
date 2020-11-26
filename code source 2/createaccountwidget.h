#ifndef CREATEACCOUNTWIDGET_H
#define CREATEACCOUNTWIDGET_H

/* La fenetre responsable de creer un compte */

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class CreateAccountWidget;
}

class CreateAccountWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccountWidget(DbManager *db, QWidget *parent = nullptr);
    ~CreateAccountWidget();

private slots:
    void on_ValiderButton_clicked();
    void on_AnnulerButton_clicked();

private:
    void closeEvent(QCloseEvent *bar);
    Ui::CreateAccountWidget *ui;
    DbManager *m_db;
};

#endif // CREATEACCOUNTWIDGET_H
