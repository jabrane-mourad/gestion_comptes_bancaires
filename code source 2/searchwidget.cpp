#include "searchwidget.h"
#include "ui_searchwidget.h"

SearchWidget::SearchWidget(DbManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);
    m_db = db;
    m_model = new QSqlQueryModel();
    setWindowTitle(QString("Rechercher Un Comptes"));

    ui->lineEdit->setPlaceholderText(QString("Numero de Compte")); // initial placeholder text
    ui->lineEdit_2->setPlaceholderText(QString("99.99"));
    ui->lineEdit_3->setPlaceholderText(QString("99.99"));
    ui->lineEdit_2->setValidator(new QDoubleValidator);
    ui->lineEdit_3->setValidator(new QDoubleValidator);
    ui->lineEdit->setValidator(new QIntValidator);


    // update textlabel at the bottom of windows from Database
    QString totalAmount = m_db->getTotalAmount() + QString(" Dh");
    QString countAccounts = m_db->getTotalAccounts();
    QString countClients = m_db->getTotalClients();
    QString avgAmounts = m_db->getAverageAmount() + QString(" Dh");
    QString avgAges = m_db->getAverageAges() + QString(" Ans");

    ui->label_10->setText(totalAmount);
    ui->label_15->setText(countAccounts);
    ui->label_16->setText(countClients);
    ui->label_17->setText(avgAmounts);
    ui->label_18->setText(avgAges);
}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::on_pushButton_clicked()
{
    /* When 'Annuler' is clicked */
    this->close();
    this->parentWidget()->show();
}

void SearchWidget::on_searshButton_clicked()
{
    /* When 'Valider' is clicked */

    int comboIndex = ui->comboBox->currentIndex();
    QString LineEditText = ui->lineEdit->text();
    QSqlQuery query(m_db->getDB());

    if ( !LineEditText.length() ){
        QMessageBox::information(this, "Erreur", "Veuillez Remplir le Champs Necessaire");
        return;
    }

    switch ( comboIndex ) {
    case 0:
        query = m_db->searchByAccountID(LineEditText.toInt());break;
    case 1:
        query = m_db->searchByNom(LineEditText);break;
    case 2:
        query = m_db->searchByPrenom(LineEditText);break;
    }


    // Display message if no record is found in the database, instead of showing empty table.
    int query_size = 0;
    while (query.next())
        ++query_size;
    if (!query_size){
        QMessageBox::information(this, "Resultat du Recherche", "Aucun Compte Trouve");
        return;
    }

    // Output data on tableview
    m_model->setQuery(query);
    ui->tableView->setModel(m_model);
    ui->tableView->setColumnWidth(0, 150);
    ui->tableView->setColumnWidth(1, 70);
    ui->tableView->setColumnWidth(2, 150);
}

void SearchWidget::on_comboBox_currentIndexChanged(int index)
{
    /* Change PlaceHolder for LineEdit each time the index is changed */

    switch ( index ) {
    case 0:
        ui->lineEdit->setPlaceholderText(QString("Numero de Compte"));
        ui->lineEdit->setValidator(new QIntValidator);
        break;
    case 1:
        ui->lineEdit->setPlaceholderText(QString("Nom..."));
        ui->lineEdit->setValidator(new QRegExpValidator);
        break;
    case 2:
        ui->lineEdit->setPlaceholderText(QString("Prenom..."));
        ui->lineEdit->setValidator(new QRegExpValidator);
        break;
    }
}

void SearchWidget::on_pushButton_2_clicked()
{
    // Seach Clients Having Multiple Account

    QString N = ui->spinBox->text();
    QSqlQuery query = m_db->searchClientsWithMultipleAccounts(N.toInt());
    tableviewwidget = new TableViewWidget(query, this);
    tableviewwidget->resize_column_width(0, 130);
    tableviewwidget->show();
}

void SearchWidget::on_pushButton_3_clicked()
{
    // Search Client who's age is in the specified range

    QString x = ui->spinBox_2->text();
    QString y = ui->spinBox_3->text();
    QSqlQuery query = m_db->searchClientsWithAgeRange(x.toInt(), y.toInt());

    tableviewwidget = new TableViewWidget(query, this);
    tableviewwidget->show();
}

void SearchWidget::on_pushButton_4_clicked()
{
    // Seach Client having Credit superior to
    QString amount = ui->lineEdit_2->text();
    if ( !amount.length() ){
        QMessageBox::warning(this, "Erreur", "Veuillez Remplir Le Champ Necessaire");
        return;
    }
    QSqlQuery query = m_db->searchClientsWithAmountComparison(amount.toDouble(), 1);

    tableviewwidget = new TableViewWidget(query, this);
    tableviewwidget->show();
}

void SearchWidget::on_pushButton_7_clicked()
{
    // When 'Annuler' is Clicked
    this->close();
    this->parentWidget()->show();
}

void SearchWidget::on_pushButton_5_clicked()
{
    // Seach Client having Credit inferior to

    QString amount = ui->lineEdit_3->text();
    if ( !amount.length() ){
        QMessageBox::warning(this, "Error", "Veuillez Remplir Le Champs Necessaire");
        return;
    }
    QSqlQuery query = m_db->searchClientsWithAmountComparison(amount.toDouble(), 0);

    tableviewwidget = new TableViewWidget(query, this);
    tableviewwidget->show();
}

void SearchWidget::on_tabWidget_tabBarClicked(int index)
{
    // Switch between tabs slot
    if ( index == 0 )
        this->resize(760, 480);
    if ( index == 1 )
        this->resize(427, 360);
}

void SearchWidget::closeEvent(QCloseEvent *bar){
    this->close();
    this->parentWidget()->show();
}
