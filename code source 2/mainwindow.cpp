#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize Database
    m_db = new DbManager();

    // connect slot of About and Exit button
    connect(ui->exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->aboutButton, SIGNAL(clicked()), this, SLOT(aboutDialogSlot()));

    // create account slot
    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(createAccountSlot()));

    // delete account slot
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteAccountSlot()));

    // search for an account
    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(findAccountSlot()));

    // update an account
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(updateAccountSlot()));

    // sort an account
    connect(ui->sortButton, SIGNAL(clicked()), this, SLOT(sortAccountSlot()));

    // transactions
    connect(ui->transactionButton, SIGNAL(clicked()), this, SLOT(transactionsSlot()));


    // add the picture to main menu
    QPixmap pix("C:\\Users\\daruom\\Desktop\\Bank20190522\\Bank20190522\\icons\\mainWindow.png");
    ui->imageLabel->setPixmap(pix.scaled(300, 300, Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aboutDialogSlot(){
    this->hide();
    QMessageBox::information(this, "A propos", "Ce programme est cree avec QT 5.12.2\nEncadre Par: El Bannay Omar\n\n"
                                               "Realise Par:\n"
                                               "\tJABRANE Mourad \n"
                                               "\tmouradjabrane1998@gmail.com   ");
    this->show();
}

void MainWindow::deleteAccountSlot(){
    this->hide();

    deletewidget = new DeleteWidget(m_db, this);
    deletewidget->show();
}

void MainWindow::findAccountSlot(){
    this->hide();

    // show the new window
    searchwidget = new SearchWidget(m_db, this);
    searchwidget->show();
}

void MainWindow::updateAccountSlot(){
    // hide the main menu
    this->hide();

    // show the child menu
    AccountClientsWidget *updatewidget = new AccountClientsWidget(m_db, this);
    updatewidget->show();
}

void MainWindow::createAccountSlot(){
    // hide the main window
    this->hide();

    // Show the new window
    CreateAccountWidget *createwidget = new CreateAccountWidget(m_db, this);
    createwidget->show();
}

void MainWindow::sortAccountSlot(){
    this->hide();
    sortwidget = new SortWidget(m_db, this);
    sortwidget->show();
}

void MainWindow::transactionsSlot(){
    this->hide();
    transactionswidget = new TransactionWidget(m_db, this);
    transactionswidget->show();
}
