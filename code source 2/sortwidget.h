#ifndef SORTWIDGET_H
#define SORTWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QSqlQueryModel>
#include "dbmanager.h"

namespace Ui {
class SortWidget;
}

class SortWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SortWidget(DbManager *db, QWidget *parent = nullptr);
    ~SortWidget();

private slots:
    void on_cancelButton_clicked();

    void on_applyButton_clicked();

private:
    void closeEvent(QCloseEvent *bar);
    Ui::SortWidget *ui;
    DbManager *m_db;
    QSqlQueryModel *m_model;
};

#endif // SORTWIDGET_H
