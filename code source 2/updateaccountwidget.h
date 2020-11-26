#ifndef UPDATEACCOUNTWIDGET_H
#define UPDATEACCOUNTWIDGET_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class UpdateAccountWidget;
}

class UpdateAccountWidget : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateAccountWidget(DbManager *db, QWidget *parent = nullptr);
    ~UpdateAccountWidget();
    void setOldValues(QString nom, QString prenom, int age, QString adresse,
                     QString tel, double solde, QString type_compte);

private:
    Ui::UpdateAccountWidget *ui;
    DbManager *m_db;
    QString nom, prenom, age, adresse, tel, solde, type_compte;
};

#endif // UPDATEACCOUNTWIDGET_H
