#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <database.h>
#include <auth.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DB *db;
    QString namvir = "";
    QString str123 = "";
    QString navant = "";
    QString str1234 = "";
    void conne(QString str, QString str2);

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_comboBox_5_activated(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_action_2_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_12_clicked();

    void on_action_4_triggered();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_pushButton_11_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    auth *au;
};
#endif // MAINWINDOW_H
