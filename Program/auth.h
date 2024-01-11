#ifndef AUTH_H
#define AUTH_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class auth;
}

class auth : public QWidget
{
    Q_OBJECT

public:
    explicit auth(QWidget *parent = nullptr);
    ~auth();

signals:
    void conbd(QString str1, QString str2);

private slots:
    void on_pushButton_clicked();

private:
    Ui::auth *ui;
};

#endif // AUTH_H
