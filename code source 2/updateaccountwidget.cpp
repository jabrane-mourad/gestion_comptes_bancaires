#include "updateaccountwidget.h"
#include "ui_updateaccountwidget.h"

UpdateAccountWidget::UpdateAccountWidget(DbManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateAccountWidget)
{
    ui->setupUi(this);
    m_db = db;


    // set line edit max length
    ui->nomLineEdit->setMaxLength(30);
    ui->prenomLineEdit->setMaxLength(30);
    ui->ageLineEdit->setMaxLength(2);
    ui->adresseLineEdit->setMaxLength(50);
    ui->telLineEdit->setMaxLength(10);

    // setup line edit validator
    ui->ageLineEdit->setValidator(new QIntValidator);
    ui->soldeLineEdit->setValidator(new QDoubleValidator);
    ui->telLineEdit->setValidator(new QDoubleValidator);

}

UpdateAccountWidget::~UpdateAccountWidget()
{
    delete ui;
}

void UpdateAccountWidget::setOldValues(QString nom, QString prenom, int age, QString adresse, QString tel, double solde, QString type_compte){
    /*
     * Set Date from Database and set them as default value for the user the change them */

}
