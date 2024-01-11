#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QComboBox>
#include <QMessageBox>
#include <QAxObject>

class DB
{
public:
    QSqlDatabase dataBase;
    QSqlQueryModel *model;
    QSqlQueryModel *modelname;
    QVector <QString> paramsNames;
    bool connectDB (QString server, QString database);
    bool connected();
    void close();
    void showView(QString &q, QTableView *tv, QComboBox *com1, QComboBox *com2, QComboBox *com3, QComboBox *com4);
    void showvirus(QString &q, QTableView *tv);
    void showtru(QString &q, QTableView *tv);
    void showfas(QString &q, QTableView *tv);
    void insertvirus(QString name, QString date, QString size, QString avtor, QString kol, QString id1, QString id2, QString id3, QString id4);
    void serach(QString &str, QTableView *tv);
    void deletvirus(QString str);
    void updatevir(QString str);
    void createWord (QString );
    void insertant(QString name, QString proiz, QString cena);
    void deletant(QString str);
    void searchant(QString &q, QTableView *tv);
    void createWordne(QString q);
    DB();
    ~DB();
};
#endif // DATABASE_H
