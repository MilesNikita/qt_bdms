#include "auth.h"
#include "ui_auth.h"


auth::auth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);

}

auth::~auth()
{
    delete ui;
}

void auth::on_pushButton_clicked()
{
    if ((ui->lineEdit->text() != "") && (ui->lineEdit_2->text() != "")){
    emit conbd(ui->lineEdit->text(), ui->lineEdit_2->text());
    this->close();}
    else
    {
        QMessageBox::critical(this, "Ошибка", "Введите нужную информацию!");
    }
}
