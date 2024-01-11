#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    au = new auth();
    connect(au, &auth::conbd, this, &MainWindow::conne);
    ui->groupBox_10->setEnabled(false);
    ui->groupBox_11->setEnabled(false);
    db = new DB();
    ui->lineEdit_7->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::conne(QString str, QString str2)
{
    db->connectDB(str, str2);
    QString q = "exec proc2";
    db->showView(q, ui->tableView, ui->comboBox, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4);
    q = "exec proc1";
    db->showvirus(q, ui->tableView_2);
    q = "select * from view1";
    db->showtru(q, ui->tableView_3);
    q = "select * from view2";
    db->showfas(q, ui->tableView_4);
    ui->groupBox->setEnabled(true);
    ui->groupBox_2->setEnabled(true);
    ui->groupBox_3->setEnabled(true);
    ui->groupBox_4->setEnabled(true);
    ui->groupBox_5->setEnabled(true);
    ui->groupBox_6->setEnabled(true);
    ui->groupBox_7->setEnabled(true);
    ui->groupBox_8->setEnabled(true);
    ui->groupBox_9->setEnabled(true);
    ui->groupBox_12->setEnabled(true);
    ui->tableView->setEnabled(true);
    ui->tableView_2->setEnabled(true);
    ui->tableView_3->setEnabled(true);
    ui->tableView_4->setEnabled(true);
}

void MainWindow::on_action_triggered()
{
    QMessageBox::about(this, "Информация о программе", "Программу разработал\nкурсант 392 учебной группы\nрядовой Погодин Н.В.");
}

void MainWindow::on_pushButton_clicked()
{
    if ((ui->lineEdit->text() != "") && (ui->lineEdit_2->text() != "") && (ui->lineEdit_3->text() != "") && (ui->lineEdit_4->text() != "")){
    db->insertvirus(ui->lineEdit->text(), ui->dateTimeEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text(), QString::number(ui->comboBox->currentIndex()), QString::number(ui->comboBox_2->currentIndex()), QString::number(ui->comboBox_3->currentIndex()), QString::number(ui->comboBox_4->currentIndex()));
    QString q = "exec proc2";
    db->showView(q, ui->tableView, ui->comboBox, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4);}
    else{
        QMessageBox::critical(this, "Ошибка", "Для занесения информации заполните все поля!");
    }
}

void MainWindow::on_comboBox_5_activated(const QString &arg1)
{
    if (ui->comboBox_5->currentText() == "По дате обнаружения")
    {
        QString maska = "00.00.0000";
        ui->lineEdit_5->setInputMask(maska);
    }
    else{
        ui->lineEdit_5->setInputMask("");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString q = "exec proc2";
    db->showView(q, ui->tableView, ui->comboBox, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->comboBox_5->currentText() == "По части названия")
    {
        QString str;
        QString name = ui->lineEdit_5->text();
        if (name != "")
        str = "select name_virus as 'Название вируса', data_poyavlenia_virusa as 'Дата обнаружения вируса', kolichestvo_izvestnix_zarazhen as 'Количество заражений' from virus where name_virus like '" + name +"' + '%'";
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
        db->serach(str, ui->tableView);
    }
    if (ui->comboBox_5->currentText() == "По количеству заражений")
    {
        QString str;
        QString name = ui->lineEdit_5->text();
        if (name != "")
        str = "select name_virus as 'Название вируса', data_poyavlenia_virusa as 'Дата обнаружения вируса', kolichestvo_izvestnix_zarazhen as 'Количество заражений' from virus where kolichestvo_izvestnix_zarazhen >= " + name + ";";
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
        db->serach(str, ui->tableView);
    }
    if (ui->comboBox_5->currentText() == "По размеру файла")
    {
        QString str;
        QString name = ui->lineEdit_5->text();
        if (name != "")
        str = "select name_virus as 'Название вируса', data_poyavlenia_virusa as 'Дата обнаружения вируса', kolichestvo_izvestnix_zarazhen as 'Количество заражений' from virus where size_code >= " + name + ";";
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
        db->serach(str, ui->tableView);
    }
    if (ui->comboBox_5->currentText() == "По дате обнаружения")
    {
        QString str;
        QString name = ui->lineEdit_5->text();
        if (name != "")
        str = "select name_virus as 'Название вируса', data_poyavlenia_virusa as 'Дата обнаружения вируса', kolichestvo_izvestnix_zarazhen as 'Количество заражений' from virus where size_code = '" + name + "';";
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
        db->serach(str, ui->tableView);
    }
    if (ui->comboBox_5->currentText() == "По автору")
    {
        QString str;
        QString name = ui->lineEdit_5->text();
        if (name != "")
        str = "select name_virus as 'Название вируса', data_poyavlenia_virusa as 'Дата обнаружения вируса', kolichestvo_izvestnix_zarazhen as 'Количество заражений' from virus where avtor_virusa like '" + name +"' + '%'";
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
        db->serach(str, ui->tableView);
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    namvir.clear();
    namvir = (index.model()->data(index.model()->index(index.row(),0)).toString());
    qDebug() << namvir;
    ui->lineEdit_6->setText(QString::number(index.row() + 1));
}

void MainWindow::on_action_2_triggered()
{
    au->show();
}
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    str123.clear();
    str123 = (index.model()->data(index.model()->index(index.row(),0)).toString());
    int stroka = index.row() + 1;
    qDebug() << str123;
    ui->lineEdit_9->setText(QString::number(stroka));
}

void MainWindow::on_pushButton_12_clicked()
{
    if (ui->comboBox_8->currentText() == "Название вируса")
    {
        QString name = ui->lineEdit_16->text();
        if (name != ""){
        QString str = "update virus set name_virus = '" + name + "' where name_virus = + '" + str123 +"'";
        db->updatevir(str);
        QString q = "exec proc2";
        db->showView(q, ui->tableView, ui->comboBox, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4);
        }
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
    }
    if (ui->comboBox_8->currentText() == "Дата обнаружения вируса")
    {
        QString name = ui->lineEdit_16->text();
        if (name != ""){
        QString str = "update virus set data_poyavlenia_virusa = '" + name + "' where name_virus = + '" + str123 +"'";
        db->updatevir(str);
        QString q = "exec proc2";
        db->showView(q, ui->tableView, ui->comboBox, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4);
        }
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
    }
    if (ui->comboBox_8->currentText() == "Размер кода")
    {
        QString name = ui->lineEdit_16->text();
        if (name != ""){
        QString str = "update virus set size_code =" + name + " where name_virus = + '" + str123 +"'";
        db->updatevir(str);
        QString q = "exec proc2";
        db->showView(q, ui->tableView, ui->comboBox, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4);
        }
        else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
    }
    if (ui->comboBox_8->currentText() == "Количество известных заражений")
    {
        QString name = ui->lineEdit_16->text();
        if (name != ""){
        QString str = "update virus set kolichestvo_izvestnix_zarazhen =" + name + " where name_virus = + '" + str123 +"'";
        db->updatevir(str);
        QString q = "exec proc2";
        db->showView(q, ui->tableView, ui->comboBox, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4);
        }
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
    }
}

void MainWindow::on_action_4_triggered()
{
    db->close();
    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    ui->groupBox_3->setEnabled(false);
    ui->groupBox_4->setEnabled(false);
    ui->groupBox_5->setEnabled(false);
    ui->groupBox_6->setEnabled(false);
    ui->groupBox_7->setEnabled(false);
    ui->groupBox_8->setEnabled(false);
    ui->groupBox_9->setEnabled(false);
    ui->groupBox_12->setEnabled(false);
    ui->tableView->setEnabled(false);
    ui->tableView->clearSpans();
    ui->tableView->clearMask();
    ui->tableView_2->setEnabled(false);
    ui->tableView_2->clearSpans();
    ui->tableView_2->clearMask();
    ui->tableView_3->setEnabled(false);
    ui->tableView_3->clearSpans();
    ui->tableView_3->clearMask();
    ui->tableView_4->setEnabled(false);
    ui->tableView_4->clearSpans();
    ui->tableView_4->clearMask();
}

void MainWindow::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked())
    {
        ui->groupBox_10->setEnabled(true);
        ui->groupBox_11->setEnabled(false);
    }
    else{
        ui->groupBox_10->setEnabled(false);
    }
}

void MainWindow::on_radioButton_2_clicked()
{
    if (ui->radioButton_2->isChecked())
    {
        ui->groupBox_11->setEnabled(true);
        ui->groupBox_10->setEnabled(false);
    }
    else{
        ui->groupBox_11->setEnabled(false);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString str = "delete from virus where name_virus = '" + namvir +"'";
    db->deletvirus(str);
    QString q = "exec proc2";
    db->showView(q, ui->tableView, ui->comboBox, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4);
}

void MainWindow::on_pushButton_6_clicked()
{
    if ((ui->lineEdit_10->text() != "") && (ui->lineEdit_11->text() != "") && (ui->lineEdit_14->text() != "")){
        db->insertant(ui->lineEdit_10->text(), ui->lineEdit_14->text(), ui->lineEdit_11->text());
        QString q = "exec proc1";
        db->showvirus(q, ui->tableView_2);
    }
    else {
        QMessageBox::critical(this, "Ошибка", "Введите данные");
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    QString name = ui->lineEdit_7->text();
    if (name != ""){
    QString q = "select * from func2('" + name + "')";
    db->createWord(q);}
    else{
        QMessageBox::critical(this, "Ошибка", "Введите дату для вывода!");
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    if (ui->comboBox_9->currentText() == "Название антивируса")
    {
        QString name = ui->lineEdit_18->text();
        if (name != ""){
        QString str = "update Antivirusnie_programmi set name_antivirus = '" + name + "' where name_antivirus =  '" + str1234 +"'";
        db->updatevir(str);
        QString q = "exec proc1";
        db->showvirus(q, ui->tableView_2);
        }
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
    }
    if (ui->comboBox_9->currentText() == "Фирма производитель")
    {
        QString name = ui->lineEdit_18->text();
        if (name != ""){
        QString str = "update virus set firma_proizvoditel = '" + name + "' where name_virus =  '" + str1234 +"'";
        db->updatevir(str);
        QString q = "exec proc1";
        db->showvirus(q, ui->tableView_2);
        }
        else
            QMessageBox::critical(this, "Ошибка", "Введите данные");
    }
    if (ui->comboBox_9->currentText() == "Стоимость подписки")
    {
        QString name = ui->lineEdit_18->text();
        if (name != ""){
        QString str = "update virus set stoimost_antivirusa = " + name + " where name_virus =  '" + str1234 +"'";
        db->updatevir(str);
        QString q = "exec proc1";
        db->showvirus(q, ui->tableView_2);
        }
        else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
    }
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    navant.clear();
    navant = (index.model()->data(index.model()->index(index.row(),0)).toString());
    qDebug() << navant;
    ui->lineEdit_15->setText(QString::number(index.row() + 1));
}

void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    str1234.clear();
    str1234 = (index.model()->data(index.model()->index(index.row(),0)).toString());
    qDebug() << str1234;
    ui->lineEdit_17->setText(QString::number(index.row() + 1));
}

void MainWindow::on_pushButton_11_clicked()
{
    QString str = "delete from Antivirusnie_programmi where name_antivirus = '" + navant + "'";
    db->deletvirus(str);
    QString q = "exec proc1";
    db->showvirus(q, ui->tableView_2);
}

void MainWindow::on_pushButton_8_clicked()
{
    QString q = "exec proc1";
    db->showvirus(q, ui->tableView_2);
}

void MainWindow::on_pushButton_7_clicked()
{
    if (ui->radioButton->isChecked())
    {
        if (ui->comboBox_9->currentText() == "По части названия")
        {
            QString name = ui->lineEdit_12->text();
            if (name != ""){
            QString str = "select * from Antivirusnie_programmi where name_antivirus = '" + name + "'";
            db->searchant(str, ui->tableView_2);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
        if (ui->comboBox_9->currentText() == "По фирме производителю")
        {
            QString name = ui->lineEdit_12->text();
            if (name != ""){
            QString str = "select * from Antivirusnie_programmi where firma_proizvoditel = '" + name + "'";
            db->searchant(str, ui->tableView_2);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
        if (ui->comboBox_9->currentText() == "По стоимости")
        {
            QString name = ui->lineEdit_12->text();
            if (name != ""){
            QString str = "select * from Antivirusnie_programmi where stoimost_antivirusa = " + name;
            db->searchant(str, ui->tableView_2);
            }
            else
                    QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
    }
    if (ui->radioButton_2->isChecked())
    {
        if ((ui->comboBox_10->currentText() == "По части названия") && (ui->comboBox_11->currentText() == "По фирме производителю"))
        {
            QString name = ui->lineEdit_19->text();
            QString name2 = ui->lineEdit_20->text();
            if ((name != "") && (name2 != "")){
            QString str = "select * from Antivirusnie_programmi where name_antivirus = '" + name + "' and firma_proizvoditel = '" + name2 + "'";
            db->searchant(str, ui->tableView_2);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
        if ((ui->comboBox_10->currentText() == "По части названия") && (ui->comboBox_11->currentText() == "По стоимости"))
        {
            QString name = ui->lineEdit_19->text();
            QString name2 = ui->lineEdit_20->text();
            if ((name != "") && (name2 != "")){
            QString str = "select * from Antivirusnie_programmi where name_antivirus = '" + name + "' and stoimost_antivirusa = " + name2;
            db->searchant(str, ui->tableView_2);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
        if ((ui->comboBox_10->currentText() == "По фирме производителю") && (ui->comboBox_11->currentText() == "По части названия"))
        {
            QString name = ui->lineEdit_19->text();
            QString name2 = ui->lineEdit_20->text();
            if ((name != "") && (name2 != "")){
            QString str = "select * from Antivirusnie_programmi where name_antivirus = '" + name2 + "' and firma_proizvoditel = '" + name + "'";
            db->searchant(str, ui->tableView_2);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
        if ((ui->comboBox_10->currentText() == "По фирме производителю") && (ui->comboBox_11->currentText() == "По стоимости"))
        {
            QString name = ui->lineEdit_19->text();
            QString name2 = ui->lineEdit_20->text();
            if ((name != "") && (name2 != "")){
            QString str = "select * from Antivirusnie_programmi where stoimost_antivirusa = " + name2 + " and firma_proizvoditel = '" + name + "'";
            db->searchant(str, ui->tableView_2);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
        if ((ui->comboBox_10->currentText() == "По стоимости") && (ui->comboBox_11->currentText() == "По части названия"))
        {
            QString name = ui->lineEdit_19->text();
            QString name2 = ui->lineEdit_20->text();
            if ((name != "") && (name2 != "")){
            QString str = "select * from Antivirusnie_programmi where name_antivirus = '" + name2 + "' and stoimost_antivirusa = " + name;
            db->searchant(str, ui->tableView_2);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
        if ((ui->comboBox_10->currentText() == "По стоимости") && (ui->comboBox_11->currentText() == "По фирме производителю"))
        {
            QString name = ui->lineEdit_19->text();
            QString name2 = ui->lineEdit_20->text();
            if ((name != "") && (name2 != "")){
            QString str = "select * from Antivirusnie_programmi where stoimost_antivirusa = " + name + " and firma_proizvoditel = '" + name2 + "'";
            db->searchant(str, ui->tableView_2);
            }
            else
                QMessageBox::critical(this, "Ошибка", "Введите данные");
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString str = ui->lineEdit_8->text();
    if (str != ""){
    QString zap = "select * from Antivirusnie_programmi where stoimost_antivirusa = " + str;
    db->createWordne(zap);}
    else{
        QMessageBox::critical(this, "Ошибка", "Введите цену!");
    }
}
