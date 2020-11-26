#include "transactionwidget.h"
#include "ui_transactionwidget.h"

TransactionWidget::TransactionWidget(DbManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransactionWidget)
{
    ui->setupUi(this);
    m_db = db;
    m_model = new QSqlQueryModel();
    this->resize(400, 200); // set automatic size at first

    // setup limits for lineedit
    ui->accountLineEdit->setPlaceholderText(QString("Numero de Compte"));
    ui->accountLineEdit_2->setPlaceholderText(QString("Numero de Compte"));
    ui->sourceLineEdit->setPlaceholderText(QString("Numero de Compte du Source"));
    ui->destinationLineEdit->setPlaceholderText(QString("Numero de Compte du Destination"));
    ui->amountLineEdit->setPlaceholderText(QString("0.0"));
    ui->amountLineEdit_2->setPlaceholderText(QString("0.0"));
    ui->amountLineEdit3->setPlaceholderText(QString("0.0"));
    ui->amountLineEdit->setValidator(new QDoubleValidator);
    ui->amountLineEdit_2->setValidator(new QDoubleValidator);
    ui->amountLineEdit3->setValidator(new QDoubleValidator);

}

TransactionWidget::~TransactionWidget()
{
    delete ui;
}

void TransactionWidget::on_cancelButton_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void TransactionWidget::on_cancelButton2_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void TransactionWidget::on_cancelButton3_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void TransactionWidget::on_tabWidget_tabBarClicked(int index)
{
    // resize window when index is changed

    if ( ( index <= 0 ) or ( index < 3))
        this->resize(400, 200);
    if ( index == 3 )
        this->resize(700, 400);
}

void TransactionWidget::on_depositButton_clicked()
{
    /* When 'Deposer' is clicked */

    QString accountid = ui->accountLineEdit->text();
    QString amount = ui->amountLineEdit->text();

    if ( !m_db->doesAccountExists( accountid.toInt() ) ){
        // output an error
        QMessageBox::warning(this, "Deposer", "Desole, Ce Compte N'Existe Pas");
        return;
    } else {
        if ( !amount.length() ) {
            QMessageBox::warning(this, "Deposer", "S'il Vous Plait, Entrez Un Montant !!!");
            return;
        } else {
            m_db->deposit(accountid.toInt(), amount.toDouble());
            QString message = QString("Operation Termine\n\nDeposition de ") + QString(amount)
                    + QString(" DH Chez ") + m_db->getAccountName(accountid.toInt()) + QString("\nMontant Total: ") +
                    m_db->getAccountAmount(accountid.toInt()) + QString(" DH");
            QMessageBox::information(this, "Deposer", message);
        }

    }
}

void TransactionWidget::on_depositButton_2_clicked()
{
    // When 'Tirer' is clicked

    QString accountid = ui->accountLineEdit_2->text();
    QString amount = ui->amountLineEdit_2->text();

    if ( !m_db->doesAccountExists( accountid.toInt()) ){
        // output error
        QMessageBox::warning(this, "Tirer", "Desole, Ce Compte n'Existe Pas");
        return;
    } else {
        if ( !amount.length() ){
            QMessageBox::warning(this, "Tirer", "Entrer Un Montant s'il vous plait");
            return;
        } else {

            // get response from database
            int dbresponse = m_db->draw(accountid.toInt(), amount.toDouble());
            qDebug() << dbresponse;
            switch ( dbresponse ) {
            case 0: // an error occured
                QMessageBox::critical(this, "Error", "Un Erreur s'est Produit");break;
            case 1: // operation succussfull
            {
                QString message = QString("Operation Termine\n\nTirage du ") + QString(amount) +
                        QString(" DH de ") + m_db->getAccountName(accountid.toInt()) + QString("\nMontant Total: ")+
                        m_db->getAccountAmount(accountid.toInt());
                QMessageBox::information(this, "Tirer", message);
                break;
            }
            case -1:    // account doesnt have the available money to draw
                QMessageBox::warning(this, "Tirer", "Operation Impossible\n\nCe Compte ne possed par le Montant requis");
                break;
            }

        }

    }
}

void TransactionWidget::on_exchangeButton_clicked()
{
    /*
     * transfert money from source to destination
     */

    QString source = ui->sourceLineEdit->text();
    QString destination =ui->destinationLineEdit->text();
    QString amount = ui->amountLineEdit3->text();

    if ( !source.length() or !destination.length() or !amount.length() ){
        QMessageBox::warning(this, "Error", "Veuillez Remplir Les Champs Necessaire");
        return;
    } else {
        if ( !m_db->doesAccountExists(source.toInt()) ){
            QMessageBox::warning(this, "Error", "Le Compte De Source n'existe PAS");
            return;
        }
        if ( !m_db->doesAccountExists(destination.toInt()) ){
            QMessageBox::warning(this, "Error", "Le Compte De Destination n'existe PAS");
            return;
        }
        int operationresponse = m_db->transfer(source.toInt(), destination.toInt(), amount.toDouble());
        switch ( operationresponse ) {
        case 0:
        {
                    QString message = QString("Transfert de ") + amount + QString(" Dh\n\nSource:\n\t") +
                            m_db->getAccountName(source.toInt()) + QString("\n\t") + m_db->getAccountAmount(source.toInt()) +
                            QString(" Dh\nDestination:\n\t")+
                            m_db->getAccountName(destination.toInt()) + QString("\n\t") + m_db->getAccountAmount(destination.toInt())+
                            QString(" Dh");
                    QMessageBox::information(this, "Transfert", message);
                    return;
                }
        case -1:
        {
            QMessageBox::warning(this, "Error", "La Source ne possede PAS le Montant requis");
            return;
        }
        case 1:
            QMessageBox::critical(this, "Error", "Un Erreur s'est produit");
            return;

        }
    }
}

void TransactionWidget::on_cancelButton_2_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void TransactionWidget::on_downloadButton_clicked()
{

    /* Slot for dispalying history of transactions */

    QSqlQuery query(m_db->getDB());

    /* get index of combo boxes */
    int typeindex = ui->typeComboBox->currentIndex();
    int sortindex = ui->sortComboBox->currentIndex();

    query = m_db->transactionsLog(typeindex, sortindex);

    // complete this code
    m_model->setQuery(query);
    ui->tableView->setModel(m_model);
    ui->tableView->setColumnWidth(1, 200); // change width of date colum
}

void TransactionWidget::closeEvent(QCloseEvent *bar){
    this->close();
    this->parentWidget()->show();
}
