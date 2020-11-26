#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "dbmanager.h"
#include "tableviewwidget.h"

namespace Ui {
class SearchWidget;
}

class SearchWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWidget(DbManager *db, QWidget *parent = nullptr);
    ~SearchWidget();

private slots:
    void on_pushButton_clicked();       // when 'Annuler' is clicked

    void on_searshButton_clicked();     // When 'Valider' is clicked

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();     // Search Clients having multiple Account

    void on_pushButton_3_clicked();     // Search Clients in age range

    void on_pushButton_4_clicked();     // Seach Client having Credit superior to

    void on_pushButton_7_clicked();     // when 'Annuler' is clicked

    void on_pushButton_5_clicked();     // Seach Client having Credit inferior to

    void on_tabWidget_tabBarClicked(int index);

private:
    void closeEvent(QCloseEvent *bar);
    Ui::SearchWidget *ui;
    DbManager *m_db;
    QSqlQueryModel *m_model;
    TableViewWidget *tableviewwidget;
};

#endif // SEARCHWIDGET_H
