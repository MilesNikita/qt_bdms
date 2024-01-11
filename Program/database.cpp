#include "database.h"
bool DB::connected()
{
    return dataBase.isOpen();
}

bool DB::connectDB (QString server, QString database)
{
    dataBase = QSqlDatabase::addDatabase("QODBC3");
    dataBase.setDatabaseName(QString("DRIVER={SQL Server};SERVER=" + server + ";DATABASE=" + database));
    if (dataBase.open()) {
        return true;
        qDebug() << dataBase.lastError().text();
    }
    qDebug() << dataBase.lastError().text();
    return false;
}

void DB::showView(QString &q, QTableView *tv, QComboBox *com1, QComboBox *com2, QComboBox *com3, QComboBox *com4)
{
    com1->clear();
    com2->clear();
    com3->clear();
    com4->clear();
    model = new QSqlQueryModel;
    model->setQuery(q);
    tv->setModel(model);
    tv->resizeColumnsToContents();
    QSqlQuery query;
    QString str1 = "select opisanie_proyavleniya from sposobi_proyavleniya";
    QVector <QString> sposob;
    if (!query.exec(str1)) return;
    while (query.next())
    {
        sposob.append(query.value(0).toString());
    }
    for (int i = 0; i < sposob.size(); i++)
        com1->addItem(sposob.at(i));
    QString str2 = "select sposob_zapuska from sposobi_zapuska";
    QVector <QString> zapusk;
    if (!query.exec(str2)) return;
    while (query.next())
        zapusk.append(query.value(0).toString());
    for(int i = 0; i < zapusk.size(); i++)
        com2->addItem(zapusk.at(i));
    QString str3 = "select sreda_obitaniya from Sredi_obitaniya_virusa";
    QVector <QString> sreda;
    if (!query.exec(str3)) return;
    while (query.next())
        sreda.append(query.value(0).toString());
    for(int i = 0; i < sreda.size(); i++)
        com3->addItem(sreda.at(i));
    QString str4 = "select sposob_maskirovki from sposobi_maskirovki";
    QVector <QString> mask;
    if (!query.exec(str4)) return;
    while (query.next())
        mask.append(query.value(0).toString());
    for(int i = 0; i < mask.size(); i++)
        com4->addItem(mask.at(i));
}

void DB::showvirus(QString &q, QTableView *tv)
{
    model = new QSqlQueryModel;
    model->setQuery(q);
    tv->setModel(model);
    tv->resizeColumnsToContents();
}

void DB::showtru(QString &q, QTableView *tv)
{
    model = new QSqlQueryModel;
    model->setQuery(q);
    tv->setModel(model);
    tv->resizeColumnsToContents();
}

void DB::showfas(QString &q, QTableView *tv)
{
    model = new QSqlQueryModel;
    model->setQuery(q);
    tv->setModel(model);
    tv->resizeColumnsToContents();
}

void DB::insertvirus(QString name, QString date, QString size, QString avtor, QString kol, QString id1, QString id2, QString id3, QString id4)
{
    QSqlQuery query;
    QString now  = "select * from virus";
    if (!query.exec(now)) return;
    int k = 1;
    while (query.next())
        k++;
    int idd1 = id1.toInt() + 1;
    int idd2 = id2.toInt() + 1;
    int idd3 = id3.toInt() + 1;
    int idd4 = id4.toInt() + 1;
    QString str = "insert into virus(ID_virusa,name_virus, data_poyavlenia_virusa, size_code, avtor_virusa, kolichestvo_izvestnix_zarazhen, ID_sposoba_proyavleniya, ID_sposoba_zapuska, ID_sredi_obitaniya, ID_sposoba_maskirovki, ID_kanala_proniknoveniya) values(" + QString::number(k) + ", '" + name + "', '" + date + "', " + size + ", '" + avtor + "', " + kol + ", " + QString::number(idd1) + ", " + QString::number(idd2) + ", " + QString::number(idd3) + ", " + QString::number(idd4) + ", 1);";
    if(!query.exec(str)){
            qDebug() << query.lastError().text() << "\n";
            qDebug() << query.executedQuery();
            return;
    }
}

void DB::serach(QString &str, QTableView *tv)
{
    modelname = new QSqlQueryModel;
    modelname->setQuery (str);
    tv->setModel(modelname);
    tv->resizeColumnsToContents();
}

void DB::deletvirus(QString str)
{
    QSqlQuery query;
    if(query.exec(str)) return;
}

void DB::updatevir(QString str)
{
    QSqlQuery query;
    if(query.exec(str)) return;
}

void DB::createWord(QString q)
{
    QSqlQuery sql;
    if (!sql.exec (q)) return;
    QAxObject *word = new QAxObject ("Word.Application");
    QAxObject *docs = word->querySubObject ("Documents");
    QAxObject *doc = docs->querySubObject ("Add()");
    QAxObject *pars = doc->querySubObject ("Paragraphs");
    QAxObject *title = pars->querySubObject ("Add()")->querySubObject ("Range()");
    title->dynamicCall ("SetRange(int, int)", 0, 50);
    title->setProperty ("Text", "Отчет об известных вирусах.\n");
    while (sql.next()) {
        QString TextStr = QString ("Название вируса - %1, Дата проявления - %2, "
                                       "Размер файла - %3, Количество известных заражений - %4.").arg (
                                  sql.value (0).toString(),
                                  sql.value (1).toString(),
                                  QString::number (sql.value (2).toInt()),
                                  sql.value (3).toString());
     auto par = pars->querySubObject ("Last");
     auto word_range = doc->querySubObject ("Content");
     par->setProperty ("Alignment", 3);
     auto range = par->querySubObject ("Range");
     range->dynamicCall ("InsertAfter(QString)", TextStr);
     word_range->dynamicCall ("InsertParagraphAfter(void)");
     delete par;
    }
    word->querySubObject ("Selection")->querySubObject ("Font")->setProperty ("Size", 12);
    word->querySubObject ("Selection")->querySubObject ("Font")->setProperty ("Name", "Times New Roman");
    word->setProperty ("Visible", true);
}

void DB::insertant(QString name, QString proiz, QString cena)
{
    QSqlQuery query;
    QString now  = "select * from Antivirusnie_programmi";
    if (!query.exec(now)) return;
    int k = 1;
    while (query.next())
        k++;
    QString str = "insert into Antivirusnie_programmi(ID_antivirusa, name_antivirus, firma_proizvoditel, stoimost_antivirusa) values(" + QString::number(k) + ", '" + name + "','" + proiz + "', " + cena + ")";
    if(!query.exec(str)){
            qDebug() << query.lastError().text() << "\n";
            qDebug() << query.executedQuery();
            return;}
}

void DB::deletant(QString str)
{
    QSqlQuery query;
    if(query.exec(str)) return;
}

void DB::searchant(QString &q, QTableView *tv)
{
    modelname = new QSqlQueryModel;
    modelname->setQuery(q);
    tv->setModel(modelname);
    tv->resizeColumnsToContents();
}

void DB::createWordne(QString q)
{
    QSqlQuery sql;
    if (!sql.exec (q)) return;
    QAxObject *word = new QAxObject ("Word.Application");
    QAxObject *docs = word->querySubObject ("Documents");
    QAxObject *doc = docs->querySubObject ("Add()");
    QAxObject *pars = doc->querySubObject ("Paragraphs");
    QAxObject *title = pars->querySubObject ("Add()")->querySubObject ("Range()");
    title->dynamicCall ("SetRange(int, int)", 0, 50);
    title->setProperty ("Text", "Отчет о стоимости антивирусных средств.\n");
    while (sql.next()) {
        QString TextStr = QString ("Название антивируса - %1, Компания производитель- %2, "
                                       "Цена - %3.").arg (
                                  sql.value (0).toString(),
                                  sql.value (1).toString(),
                                  QString::number (sql.value (2).toInt()));
     auto par = pars->querySubObject ("Last");
     auto word_range = doc->querySubObject ("Content");
     par->setProperty ("Alignment", 3);
     auto range = par->querySubObject ("Range");
     range->dynamicCall ("InsertAfter(QString)", TextStr);
     word_range->dynamicCall ("InsertParagraphAfter(void)");
     delete par;
    }
    word->querySubObject ("Selection")->querySubObject ("Font")->setProperty ("Size", 12);
    word->querySubObject ("Selection")->querySubObject ("Font")->setProperty ("Name", "Times New Roman");
    word->setProperty ("Visible", true);
}

void DB::close()
{
    if (dataBase.isOpen()) dataBase.close();
}
DB::DB() {};
