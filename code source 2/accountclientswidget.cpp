#include "accountclientswidget.h"
#include "ui_accountclientswidget.h"

AccountClientsWidget::AccountClientsWidget(DbManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountClientsWidget)
{
    ui->setupUi(this);
    setWindowTitle(QString("Modifier Un Compte"));
    m_db = db;
    m_model = new QSqlQueryModel();
    nom = QString(""); prenom = QString(""); accountid = QString("");
    m_clientID = new QString(); m_accountID = new QString();

    connect(ui->firstRadioButton, SIGNAL(toggled(bool)), this, SLOT(searchByIDSlot(bool)));
    connect(ui->secondRadioButton, SIGNAL(toggled(bool)), this, SLOT(searchByNomSlot(bool)));
    connect(ui->thirdRadioButton, SIGNAL(toggled(bool)), this, SLOT(searchByPrenomSlot(bool)));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchButtonSlot()));
    connect(this, SIGNAL(searchSignal()), this, SLOT(searchDBSlot()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonSlot()));

    // set Validator for lineEdits
    ui->lineEdit->setMaxLength(30);
    ui->lineEdit_2->setMaxLength(30);
    ui->lineEdit_3->setMaxLength(2);
    ui->lineEdit_5->setMaxLength(50);
    ui->lineEdit_4->setMaxLength(10);
    ui->lineEdit_4->setValidator(new QDoubleValidator); // validator for phone numebr
    ui->lineEdit_3->setValidator(new QIntValidator);    // validator for age
}

AccountClientsWidget::~AccountClientsWidget()
{
    delete ui;
}

void AccountClientsWidget::searchByIDSlot(bool checked){
    // Change text label above the input lineEdit

    if ( checked ){
        ui->inputLabel->setText(QString("Numero De Compte:"));
        ui->inputLineEdit->setValidator(new QIntValidator);
    }
}

void AccountClientsWidget::searchByNomSlot(bool checked){
    // Change text label above the input lineEdit

    if ( checked ){
        ui->inputLabel->setText(QString("Nom:"));
        ui->inputLineEdit->setValidator(new QRegExpValidator);
    }
}

void AccountClientsWidget::searchByPrenomSlot(bool checked){
    // Change text label above the input lineEdit

    if ( checked ) {
        ui->inputLabel->setText(QString("Prenom: "));
        ui->inputLineEdit->setValidator(new QRegExpValidator);
    }
}

void AccountClientsWidget::searchButtonSlot(){
    /* When 'Rechercher' is clicked */

    if ( ui->firstRadioButton->isChecked() ){

       accountid = ui->inputLineEdit->text();
       if ( !accountid.length() )
            QMessageBox::warning(this, "Erreur", "Entrez Le Numero De Compte");
       else
           emit searchSignal();

       return;
    } else if ( ui->secondRadioButton->isChecked() ){

        nom = ui->inputLineEdit->text();
        if ( !nom.length() )
            QMessageBox::warning(this, "Erreur", "Entrez Le Nom");
        else
            emit searchSignal();

        return;
    } else if ( ui->thirdRadioButton->isChecked() ){

        prenom = ui->inputLineEdit->text();
        if ( !prenom.length() )
            QMessageBox::warning(this, "Erreur", "Entrez Le Prenom");
        else
            emit searchSignal();

        return;
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez Specifier Une Option De Recherche");
        return;
    }
}

void AccountClientsWidget::searchDBSlot(){
    /* Search Database & Output Data as TableView */

    QString user_input = ui->inputLineEdit->text();
    QSqlQuery query(m_db->getDB());

    if ( ui->firstRadioButton->isChecked() && user_input.length() ){
        query.prepare("SELECT id_compte, nom, prenom, solde, date_creation, tel "
                      "FROM comptes JOIN clients ON "
                      "comptes.id_client = clients.id_client WHERE id_compte=:id_compte");
        query.bindValue(":id_compte", user_input.toInt());
        query.exec();
    }
    if ( ui->secondRadioButton->isChecked() && user_input.length() ){
        query.prepare("select id_compte, nom, prenom, solde, date_creation, tel from comptes join clients on comptes.id_client = clients.id_client where clients.nom=:nom;");
        query.bindValue(":nom", user_input);
        query.exec();
    }
    if ( ui->thirdRadioButton->isChecked() && user_input.length() ){
        query.prepare("select id_compte, nom, prenom, solde, date_creation, tel from comptes join clients on comptes.id_client = clients.id_client where clients.prenom=:prenom;");
        query.bindValue(":prenom", user_input);
        query.exec();
    }

    m_model->setQuery(query);
    ui->tableView->setModel(m_model);

}

void AccountClientsWidget::cancelButtonSlot(){
    this->close();
    this->parentWidget()->show();
}

void AccountClientsWidget::on_tableView_clicked(const QModelIndex &index)
{
    /* When user click a record on the tableView, output the information in the Form */


    int selectedRow = index.row();
    qDebug() << "Selected Row: " << selectedRow;

    // get client id from selected row
    unsigned long long accountID = m_model->data(m_model->index(selectedRow, 0)).toULongLong();
    qDebug() << "Account id: " << accountID;

    // display data on the form
    QSqlQuery query(m_db->getDB());
    query = m_db->searchByAccountID(int(accountID));

    query.next(); // set Cursor on the first record
    QString Nom = query.value(5).toString();
    QString Prenom = query.value(6).toString();
    QString Age = query.value(7).toString();
    QString Adresse = query.value(8).toString();
    QString Tel = query.value(9).toString();
    QString typeDeCompte = (query.value(4).toString());

    qDebug() << "Nom: " << Nom;
    qDebug() << "Prenom: " << Prenom;
    qDebug() << "Age: " << Age;
    qDebug() << "Adresse: " << Adresse;
    qDebug() << "Tel: " << Tel;
    qDebug() << "Type de Compte: " << typeDeCompte;

    ui->lineEdit->setText(Nom);
    ui->lineEdit_2->setText(Prenom);
    ui->lineEdit_3->setText(Age);
    ui->lineEdit_4->setText(QString("0") + Tel);
    ui->lineEdit_5->setText(Adresse);
    if ( typeDeCompte == QString("Etudiant (e)"))
        ui->comboBox_2->setCurrentIndex(0);
    if ( typeDeCompte == QString("Sans-Travail"))
        ui->comboBox_2->setCurrentIndex(1);
    if ( typeDeCompte == QString("Fonctionnaire"))
        ui->comboBox_2->setCurrentIndex(2);


    // set member variable for another use ( Slot Below )
    *m_clientID = query.value(1).toString();
    *m_accountID = query.value(0).toString();
}

void AccountClientsWidget::on_pushButton_clicked()
{
    /* When 'Sauvgarder' is clicked, update the database */

    // get data from the From
    QString Nom = ui->lineEdit->text();
    QString Prenom = ui->lineEdit_2->text();
    QString Age = ui->lineEdit_3->text();
    QString Tel = ui->lineEdit_4->text();
    QString Adresse = ui->lineEdit_5->text();
    QString TypeDeCompte = ui->comboBox_2->currentText();

    // update datebase
    bool updateStatus1 = m_db->updateClient((*m_clientID).toInt(), Nom, Prenom, Age.toInt(), Adresse, Tel);
    bool updateStatus2 = m_db->updateAccountType((*m_accountID).toInt(), TypeDeCompte);


    // Display Mesasge for the user
    if ( updateStatus1 && updateStatus2 ){
        QMessageBox::information(this, "Modifier Un Compte", "Donnee Modifie Avec Succes");
    } else {
        QMessageBox::critical(this, "Modifier Un Compte", "Une Erreur s\'est Produite");
    }
}

void AccountClientsWidget::closeEvent(QCloseEvent *bar){
    this->close();
    this->parentWidget()->show();
}
