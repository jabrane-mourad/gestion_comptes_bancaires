#ifndef DELETEWIDGET_H
#define DELETEWIDGET_H

#include <QWidget>
#include <QDialog>
#include "dbmanager.h"
#include <QMessageBox>
#include <QDoubleValidator>

namespace Ui {
class DeleteWidget;
}

class DeleteWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteWidget(DbManager *db, QWidget *parent = nullptr);
    ~DeleteWidget();

private slots:
    void on_cancelButton_clicked();

    void on_deleteButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    void closeEvent(QCloseEvent *bar);
    Ui::DeleteWidget *ui;
    DbManager *m_db;
};

#endif // DELETEWIDGET_H
