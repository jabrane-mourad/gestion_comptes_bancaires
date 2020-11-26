#include "tableviewwidget.h"
#include "ui_tableviewwidget.h"

TableViewWidget::TableViewWidget(QSqlQuery query, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableViewWidget)
{
    ui->setupUi(this);
    m_model = new QSqlQueryModel();

    m_model->setQuery(query);
    ui->tableView->setModel(m_model);
}

TableViewWidget::~TableViewWidget()
{
    delete ui;
}

void TableViewWidget::on_pushButton_clicked()
{
    this->close();
    this->parentWidget()->show();
}

void TableViewWidget::resize_column_width(int col, int width){
    ui->tableView->setColumnWidth(col, width);
}

void TableViewWidget::closeEvent(QCloseEvent *bar){
    this->close();
    this->parentWidget()->show();

}
