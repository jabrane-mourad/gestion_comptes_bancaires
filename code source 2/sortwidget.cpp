#include "sortwidget.h"
#include "ui_sortwidget.h"

SortWidget::SortWidget(DbManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortWidget)
{
    ui->setupUi(this);
    m_db = db;
    m_model = new QSqlQueryModel();
    this->showMaximized();
}

SortWidget::~SortWidget()
{
    delete ui;
}

void SortWidget::on_cancelButton_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void SortWidget::on_applyButton_clicked()
{
    int comboBoxIndex = ui->comboBox->currentIndex();
    qDebug() << "ComboBox Index: " << comboBoxIndex;

    QSqlQuery query(m_db->getDB());

    switch ( comboBoxIndex ) {
    case 0:
        query = m_db->sortByAccountId();
        break;
    case 1:
        query = m_db->sortByDate();
        break;
    case 2:
        query = m_db->sortByCredit();
        break;
    case 3:
        query = m_db->sortByNom();
        break;
    case 4:
        query = m_db->sortByPrenom();
        break;
    }

    // output result on tableview
    m_model->setQuery(query);
    ui->tableView->setModel(m_model);
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(4, 170);
    ui->tableView->setColumnWidth(6, 210);
}

void SortWidget::closeEvent(QCloseEvent *bar){
    this->close();
    this->parentWidget()->show();
}
