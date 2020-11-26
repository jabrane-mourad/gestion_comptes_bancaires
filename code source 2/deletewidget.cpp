#include "deletewidget.h"
#include "ui_deletewidget.h"

DeleteWidget::DeleteWidget(DbManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteWidget)
{
    ui->setupUi(this);
    setWindowTitle(QString("Supprimer Un Compte"));
    m_db = db;
    ui->lineEdit->setPlaceholderText(QString("0"));
    ui->lineEdit->setValidator(new QDoubleValidator);
}

DeleteWidget::~DeleteWidget()
{
    delete ui;
}

void DeleteWidget::on_cancelButton_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void DeleteWidget::on_deleteButton_clicked()
{

    // check if account exists already or not
    if ( !m_db->doesAccountExists( ui->lineEdit->text().toInt() ) ){
        QMessageBox::warning(this, "Erreur", "Ce Compte N\'existe Pas !!!");
        return;
    }
    int reponse = QMessageBox::question(this, "Erreur", "Voulez Vous Vraiment Supprimer Ce Compte ?\n\n", QMessageBox::Yes|QMessageBox::No);

    if ( reponse == QMessageBox::Yes ){
        m_db->deleteAccount(ui->lineEdit->text().toInt());
        QMessageBox::information(this, "Success", "Compte Supprime Avec Succes");
    }
}

void DeleteWidget::on_lineEdit_textChanged(const QString &arg1)
{
    /* Display account information when LineEdit data changed */

    QSqlQuery query;

    if ( m_db->doesAccountExists(arg1.toInt()) ){
        query = m_db->getAccount(arg1.toInt());

        // Prepare the message to display
        QString NumeroDeCompte = QString("Numero De Compte:\t") + query.value(0).toString() + QString("\n");
        QString NomPrenom = QString("Nom Et Prenom:\t") + query.value(6).toString() + QString(" ") + query.value(7).toString() + QString("\n");
        QString age = QString("Age:\t") + query.value(8).toString() + QString("\n");
        QString adresse = QString("Adresse:\t") + query.value(9).toString() + QString("\n");
        QString tel = QString("Telephone:\t+212") + query.value(10).toString() + QString("\n");
        QString dateCreation = QString("Date de Creation:\t") + query.value(1).toString() + QString("\n");
        QString solde = QString("Solde (Dh):\t") + query.value(2).toString() + QString("\n");
        QString type = QString("Type De Compte:\t") + query.value(3).toString() + QString("\n");

        QString messageToDisplay = NumeroDeCompte + NomPrenom + solde + dateCreation + type + age + adresse + tel;

        ui->textBrowser->setText(messageToDisplay);
    } else {
        ui->textBrowser->setText(QString("Compte Introuvable !!!!"));
    }


}

void DeleteWidget::closeEvent(QCloseEvent *bar){
    this->close();
    this->parentWidget()->show();
}
