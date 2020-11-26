#include "createaccountwidget.h"
#include "ui_createaccountwidget.h"
#include "mainwindow.h"
#include <QWidget>
#include <QDialog>

CreateAccountWidget::CreateAccountWidget(DbManager *db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccountWidget)
{
    ui->setupUi(this);
    setWindowTitle(QString("Creer Un Compte"));
    m_db = db;  // use the same database as the parent widget

    // setup line edit placeholder
    ui->nomLineEdit->setPlaceholderText(QString("Votre Nom"));
    ui->prenomLineEdit->setPlaceholderText(QString("Votre Prenom"));
    ui->ageLineEdit->setPlaceholderText(QString("18"));
    ui->adresseLineEdit->setPlaceholderText(QString("Votre Adresse"));
    ui->telLineEdit->setPlaceholderText(QString("Votre Numero de Telephone"));
    ui->soldeLineEdit->setPlaceholderText(QString("100.00"));

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

CreateAccountWidget::~CreateAccountWidget()
{
    delete ui;
}

void CreateAccountWidget::on_ValiderButton_clicked()
{
    this->hide();
    MainWindow mainwindow;

    // Get data from user
    QString nom = ui->nomLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString adresse = ui->adresseLineEdit->text();
    QString tel = ui->telLineEdit->text();
    int age = ui->ageLineEdit->text().toInt();
    double solde = ui->soldeLineEdit->text().toDouble();
    QString type_compte = ui->typeComboBox->currentText();


    // Check errors or empty fields.
    if ( !nom.length() ){
        QMessageBox::warning(this, "Erreur", "Entrez Un Nom");
        this->show();
    } else if (!prenom.length() ){
        QMessageBox::warning(this, "Erreur", "Entrez Un Prenom");
        this->show();
    } else if (!adresse.length() ) {
        QMessageBox::warning(this, "Erreur", "Entrez Une Adresse");
        this->show();
    } else if ( tel.length() != 10 ){
        QMessageBox::warning(this, "Erreur", "Entrez Un Numero de Telephone Valide" );
        this->show();
    } else if ( !QString(age).length() ) {
        QMessageBox::warning(this, "Erreur", "Entrez Un Age" );
        this->show();
    } else if ( ! solde ) {
        QMessageBox::warning(this, "Erreur", "Entrez Un Solde");
        this->show();
    } else {
        /* This block is Executed when no error from user is encountred */


        // If Client already exists add only new Account associated with that client
        if ( m_db->isClientRedoundant(nom, prenom, age, adresse, tel.toInt()) ) {

            qDebug() << "Client is Redundant";

            int id_client = m_db->getClientID(nom, prenom, age, adresse, tel.toInt()); // get client's ID
            m_db->addAccount(solde, type_compte, id_client);
            QMessageBox::information(this, "Succes", "Ce Client Existe Deja\n\nUn Nouveau Compte Associe Avec Ce Client a ete Cree Avec Succes");
        } else {
            // Add client & account
            m_db->addClient(nom, prenom, age, adresse, tel.toInt());
            int id_client = m_db->getClientID(nom, prenom, age, adresse, tel.toInt()); // get client's ID
            m_db->addAccount(solde, type_compte, id_client);
            QMessageBox::information(this, "Succes", "Un Nouveau Compte a ete Cree Avec Succes");
        }
        this->parentWidget()->show();
    }
}

void CreateAccountWidget::on_AnnulerButton_clicked()
{
    // return to Main Menu
    this->parentWidget()->show();
    this->close();
}

void CreateAccountWidget::closeEvent(QCloseEvent *bar){
    this->close();
    this->parentWidget()->show();
}
