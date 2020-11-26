#ifndef TABLEVIEWWIDGET_H
#define TABLEVIEWWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDialog>

namespace Ui {
class TableViewWidget;
}

class TableViewWidget : public QDialog
{
    Q_OBJECT

public:
    explicit TableViewWidget(QSqlQuery query, QWidget *parent = nullptr);
    ~TableViewWidget();
    void resize_column_width(int col, int width);

private slots:
    void on_pushButton_clicked();      // When cancel button is clicked

private:
    void closeEvent(QCloseEvent *bar);
    Ui::TableViewWidget *ui;
    QSqlQueryModel *m_model;
};

#endif // TABLEVIEWWIDGET_H
